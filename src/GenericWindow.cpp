#include "Sgl/OpenGL.h"
#include "Sgl/GenericWindow.h"
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
	GenericWindow::GenericWindow(WindowProperties props) :
		Window(props),
		vSyncOn(true),
		fullScreen(false),
		framesPerSecond(-1),
		nbFrames(0)
	{}

	GenericWindow::~GenericWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	Window* Window::Create(WindowProperties props)
	{
		auto window = new GenericWindow(props);
		if (window->Init() == -1) {
			delete window;
			return nullptr;
		}
		return window;
	}

	bool GenericWindow::IsClosed() const
	{
		return glfwWindowShouldClose(window);
	}


	void GenericWindow::SetFPS(int fps)
	{
		framesPerSecond = fps;
	}

	void GenericWindow::MeasureFPS(int& nbFrames, double& lastTime)
	{
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last print was more than 1 sec ago
			// Print and reset timer
			auto time = 1000.0 / double(nbFrames);
			SglCoreTrace("{} ms/frame ({} FPS)", time, 1000 * (1 / time));
			nbFrames = 0;
			lastTime += 1.0;
		}
	}

	void GenericWindow::Clear()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void GenericWindow::Update()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();

		MeasureFPS(nbFrames, fpsCounter);

		if (framesPerSecond == -1)
			return;

		std::this_thread::sleep_until(delay);
		delay += std::chrono::nanoseconds(1000000000) / framesPerSecond;
	}

	void GenericWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		vSyncOn = enabled;
	}

	void GenericWindow::ToggleFullScreen()
	{
		auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		if (fullScreen) {
			glfwSetWindowMonitor(window, nullptr, windowedXPos, windowedYPos, props.width, props.height, GLFW_DONT_CARE);
		}
		else {
			glfwGetWindowPos(window, &windowedXPos, &windowedYPos);
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
		}

		fullScreen = !fullScreen;
	}

	bool GenericWindow::IsVSync()
	{
		return vSyncOn;
	}

	bool GenericWindow::IsFullScreen()
	{
		return fullScreen;
	}

	int GenericWindow::Init()
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

		if(props.resizable)
			glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		else
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

		// Callback when the window gets resized
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);
			win.CallEventHandler(new WindowResizedEvent(width, height));
		});

		// Callback to set the viewport to match the new size of the window
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});

		// Drop Event
		glfwSetDropCallback(window, [](GLFWwindow* window, int count, const char** paths) {
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);
			win.CallEventHandler(new DropEvent(count, paths));
		});

		// Mouse Events
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);

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
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {

				// Fullscreen (Alt-Enter) TODO: Set on client side
				if (key == SGL_KEY_ENTER && Input::IsKeyPressed(SGL_KEY_LEFT_ALT))
					win.ToggleFullScreen();

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
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);
			win.CallEventHandler(new WindowCloseEvent);
		});

		// Initialize OpenGL for desktop
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			SglCoreError("Failed to initialize Glad");
			return -1;
		}

		glEnable(GL_MULTISAMPLE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		fpsCounter   = glfwGetTime(); // This may or may not cause problems since its called too early.
        delay = std::chrono::high_resolution_clock::now();

		return 1;
	}
}
