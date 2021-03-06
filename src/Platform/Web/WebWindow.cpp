#include "Sgl/OpenGL.h"
#include "Sgl/Platform/Web/WebWindow.h"
#include "Sgl/Events/KeyEvent.h"
#include "Sgl/Events/KeyCodes.h"
#include "Sgl/Events/ApplicationEvent.h"
#include "Sgl/Events/MouseEvent.h"
#include "Sgl/Log.h"
#include "Sgl/Input.h"

#include "GLFW/glfw3.h"

namespace sgl
{

	WebWindow::WebWindow(WindowProperties props)
		: Window(props)
		, vSyncOn(true)
		, fullScreen(false)
	{}

	WebWindow::~WebWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	Window* Window::Create(WindowProperties props)
	{
		auto window = new WebWindow(props);
		if (window->TryInit() == -1) {
			delete window;
			return nullptr;
		}
		return window;
	}

	bool WebWindow::IsClosed() const
	{
		return glfwWindowShouldClose(window);
	}

	void WebWindow::Clear()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void WebWindow::Update()
	{
        glfwSwapBuffers(window);
        glfwPollEvents();
	}

	void WebWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		vSyncOn = enabled;
	}

	static int EmscriptenResizeCallback(int eventType, const EmscriptenFullscreenChangeEvent* event, void* data)
	{
        SGL_CORE_TRACE("Resized");
		WebWindow& win = *(WebWindow*)glfwGetWindowUserPointer((GLFWwindow*)data);
		if (event->isFullscreen) {
			win.CallEventHandler(new WindowResizedEvent(event->elementWidth, event->elementHeight));
			win.fullScreenWidth = event->elementWidth;
			win.fullScreenHeight = event->elementHeight;
		}
		else {
			win.CallEventHandler(new WindowResizedEvent(win.props.width, win.props.height));
		}
		return EMSCRIPTEN_RESULT_SUCCESS;
	}

	void WebWindow::SetFullscreen()
	{
		#ifdef SGL_SOFT_FULLSCREEN
		SetSoftFullscreen();
		#else
		SetStandardFullscreen();
		#endif
	}

    void WebWindow::SetWindowed()
    {
        #ifdef SGL_SOFT_FULLSCREEN
        ExitSoftFullscreen();
        #else
        ExitStandardFullscreen();
        #endif
    }

	bool WebWindow::IsVSync()
	{
		return vSyncOn;
	}

	bool WebWindow::IsFullScreen()
	{
		return fullScreen;
	}

	int WebWindow::TryInit()
	{
		if (!glfwInit()) {
			SGL_CORE_ERROR("glfwInit failed!");
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ES_API);
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		SetVSync(true);

		window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
		if (!window) {
			glfwTerminate();
			SGL_CORE_ERROR("glfwCreateWindow failed!");
			return -1;
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);

		emscripten_set_fullscreenchange_callback(NULL, (void*)window, EM_FALSE, &EmscriptenResizeCallback);

		// Callback when the window gets resized
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			WebWindow& win = *(WebWindow*)glfwGetWindowUserPointer(window);
			win.CallEventHandler(new WindowResizedEvent(width, height));
		});

		// Callback to set the viewport to match the new size of the window
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});

		// Drop Event
		glfwSetDropCallback(window, [](GLFWwindow* window, int count, const char** paths) {
			WebWindow& win = *(WebWindow*)glfwGetWindowUserPointer(window);
			win.CallEventHandler(new DropEvent(count, paths));
		});

		// Mouse Events
        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WebWindow& win = *(WebWindow*)glfwGetWindowUserPointer(window);
            win.CallEventHandler(new MouseScrolledEvent(xOffset, yOffset));
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
            WebWindow& win = *(WebWindow*)glfwGetWindowUserPointer(window);
            win.CallEventHandler(new MouseMovedEvent(xpos, ypos));
        });

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			WebWindow& win = *(WebWindow*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				win.CallEventHandler(new MouseButtonPressed(button));
				break;
			}
			case GLFW_RELEASE: {
				win.CallEventHandler(new MouseButtonReleased(button));
				break;
			}
			}
		});

		// Key Events
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WebWindow& win = *(WebWindow*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {

				win.CallEventHandler(new KeyPressedEvent(key, 0));
				break;
			}
			case GLFW_RELEASE: {
				win.CallEventHandler(new KeyReleasedEvent(key));
				break;
			}
			case GLFW_REPEAT: {
				win.CallEventHandler(new KeyPressedEvent(key, 1));
				break;
			}
			}
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			WebWindow& win = *(WebWindow*)glfwGetWindowUserPointer(window);
			win.CallEventHandler(new WindowCloseEvent);
		});

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		return 1;
	}

	void WebWindow::SetSoftFullscreen()
	{
        EmscriptenFullscreenStrategy strategy = {
                .scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_DEFAULT,
                .canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF,
                .filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT
        };
        emscripten_enter_soft_fullscreen(NULL, &strategy);
        fullScreen = false;
	}

    void WebWindow::ExitSoftFullscreen()
    {
        emscripten_exit_soft_fullscreen();
    }

    void WebWindow::ExitStandardFullscreen()
    {
        emscripten_exit_fullscreen();
        fullScreen = false;
    }

	void WebWindow::SetStandardFullscreen()
	{
        emscripten_exit_soft_fullscreen();
        EM_ASM(JSEvents.inEventHandler = true);
        EM_ASM(JSEvents.currentEventHandler = { allowsDeferredCalls:true });
        EmscriptenFullscreenStrategy strategy = {
            .scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_DEFAULT,
            .canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF,
            .filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT
        };
        emscripten_request_fullscreen_strategy(NULL, EM_FALSE, &strategy);
        fullScreen = true;
	}

}