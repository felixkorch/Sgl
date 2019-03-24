#include "Sgl/OpenGL.h"
#include "Sgl/Platform/Web/WebWindow.h"
#include "Sgl/Events/KeyEvent.h"
#include "Sgl/Events/KeyCodes.h"
#include "Sgl/Events/ApplicationEvent.h"
#include "Sgl/Events/MouseEvent.h"
#include "Sgl/Log.h"
#include "Sgl/Input.h"

namespace sgl
{

	WebWindow::WebWindow(int width, int height, const char* title)
		: props{ width, height, title }, vSyncOn(true), fullScreen(false) {}

	WebWindow::~WebWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	Window* Window::Create(unsigned int width, unsigned int height, const char* title)
	{
		auto window = new WebWindow(width, height, title);
		if (window->Init() == -1) {
			delete window;
			return nullptr;
		}
		return window;
	}

	bool WebWindow::IsClosed() const
	{
		return glfwWindowShouldClose(window);
	}

	void WebWindow::Clear() const
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void WebWindow::Update() const
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

	void WebWindow::ToggleFullScreen()
	{
		#ifdef WEB_SOFT_FULLSCREEN
		ToggleSoftFullScreen();
		#else
		ToggleStandardFullScreen();
		#endif
	}

	int WebWindow::Init()
	{
		if (!glfwInit()) {
			SglCoreError("glfwInit failed!");
			return -1;
		}

		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		SetVSync(true);

		window = glfwCreateWindow(props.width, props.height, props.title, nullptr, nullptr);
		if (!window) {
			glfwTerminate();
			SglCoreError("glfwCreateWindow failed!");
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

				// Fullscreen (Alt-Enter) TODO: Set on client side
				if (key == SGL_KEY_ENTER && Input::IsKeyPressed(SGL_KEY_LEFT_ALT))
					win.ToggleFullScreen();
				else if (key == SGL_KEY_ESCAPE && win.fullScreen) {
					win.ToggleFullScreen();
					win.fullScreen = false;
				}

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

	void WebWindow::ToggleSoftFullScreen()
	{
		if (fullScreen) {
			emscripten_exit_soft_fullscreen();
		}
		else {
			EmscriptenFullscreenStrategy strategy = {
				.scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_DEFAULT,
				.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF,
				.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT
			};
			emscripten_enter_soft_fullscreen(NULL, &strategy);
		}

		fullScreen = !fullScreen;
	}

	void WebWindow::ToggleStandardFullScreen()
	{
		if (fullScreen) {
			emscripten_exit_fullscreen();
		}
		else {
			emscripten_exit_soft_fullscreen();
			EM_ASM(JSEvents.inEventHandler = true);
			EM_ASM(JSEvents.currentEventHandler = { allowsDeferredCalls:true });
			EmscriptenFullscreenStrategy strategy = {
				.scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_DEFAULT,
				.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF,
				.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT
			};
			emscripten_request_fullscreen_strategy(NULL, EM_FALSE, &strategy);
		}

		fullScreen = !fullScreen;
	}

}