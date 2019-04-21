#include "Sgl/OpenGL.h"
#include "Sgl/BaseWindow.h"
#include "Sgl/Events/KeyEvent.h"
#include "Sgl/Events/KeyCodes.h"
#include "Sgl/Events/ApplicationEvent.h"
#include "Sgl/Events/MouseEvent.h"
#include "Sgl/Input.h"
#include "Sgl/Log.h"

#include <functional>
#include <array>

namespace sgl
{
	BaseWindow::BaseWindow(WindowProperties props) :
		Window(props),
		vSyncOn(true),
		fullScreen(false),
		framesPerSecond(-1),
		frames(0)
	{}

	BaseWindow::~BaseWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	Window* Window::Create(WindowProperties props)
	{
		auto window = new BaseWindow(props);
		if (window->TryInit() == -1) {
			delete window;
			return nullptr;
		}
		return window;
	}

	bool BaseWindow::IsClosed() const
	{
		return glfwWindowShouldClose(window);
	}


	void BaseWindow::SetFPS(int fps)
	{
		framesPerSecond = fps;
	}

    int& BaseWindow::GetFPS()
    {
        return framesPerSecond;
    }

    void BaseWindow::DebugPrintFPS(int& nbFrames, double& lastTime)
	{
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last print was more than 1 sec ago
			// Print and reset timer
			auto time = 1000.0 / double(nbFrames);
			SGL_CORE_TRACE("{} ms/frame ({} FPS)", time, 1000 * (1 / time));
			nbFrames = 0;
			lastTime += 1.0;
		}
	}

	void BaseWindow::Clear()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void BaseWindow::Update()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();

        #ifndef NDEBUG
        DebugPrintFPS(frames, frameDelay);
        #endif

		if (framesPerSecond == -1)
			return;

		std::this_thread::sleep_until(delay);
		delay += std::chrono::nanoseconds(1000000000) / framesPerSecond;
	}

	void BaseWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		vSyncOn = enabled;
	}

	void BaseWindow::SetFullscreen()
	{
        auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwGetWindowPos(window, &windowedXPos, &windowedYPos);
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
		fullScreen = true;
	}

    void BaseWindow::SetWindowed()
    {
        glfwSetWindowMonitor(window, nullptr, windowedXPos, windowedYPos, props.width, props.height, GLFW_DONT_CARE);
        fullScreen = false;
    }

	bool BaseWindow::IsVSync()
	{
		return vSyncOn;
	}

	bool BaseWindow::IsFullScreen()
	{
		return fullScreen;
	}

	int BaseWindow::TryInit()
	{
		if (!glfwInit()) {
			SGL_CORE_ERROR("glfwInit failed!");
			return -1;
		}

		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		if(props.resizable)
			glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		else
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

		// Callback when the window gets resized
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			BaseWindow& win = *(BaseWindow*)glfwGetWindowUserPointer(window);
			win.CallEventHandler(new WindowResizedEvent(width, height));
		});

		// Callback to set the viewport to match the new size of the window
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});

		// Drop Event
		glfwSetDropCallback(window, [](GLFWwindow* window, int count, const char** paths) {
			BaseWindow& win = *(BaseWindow*)glfwGetWindowUserPointer(window);
			win.CallEventHandler(new DropEvent(count, paths));
		});

		// Mouse Events
        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
            BaseWindow& win = *(BaseWindow*)glfwGetWindowUserPointer(window);
            win.CallEventHandler(new MouseScrolledEvent(xOffset, yOffset));
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
            BaseWindow& win = *(BaseWindow*)glfwGetWindowUserPointer(window);
            win.CallEventHandler(new MouseMovedEvent(xpos, ypos));
        });

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			BaseWindow& win = *(BaseWindow*)glfwGetWindowUserPointer(window);

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
        glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode) {
            BaseWindow& win = *(BaseWindow*)glfwGetWindowUserPointer(window);
            win.CallEventHandler(new KeyTypedEvent(keycode));
        });

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			BaseWindow& win = *(BaseWindow*)glfwGetWindowUserPointer(window);

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
			BaseWindow& win = *(BaseWindow*)glfwGetWindowUserPointer(window);
			win.CallEventHandler(new WindowCloseEvent);
		});

		// Initialize OpenGL for desktop
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			SGL_CORE_ERROR("Failed to initialize Glad");
			return -1;
		}

		glEnable(GL_MULTISAMPLE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		frameDelay = glfwGetTime(); // This may or may not cause problems since its called too early.
        delay = std::chrono::steady_clock::now();

		return 1;
	}
}
