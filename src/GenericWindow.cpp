#include "Sgl/OpenGL.h"
#include "Sgl/GenericWindow.h"
#include "Sgl/Events/KeyEvent.h"
#include "Sgl/Events/ApplicationEvent.h"
#include "Sgl/Events/MouseEvent.h"
#include "Sgl/Input.h"
#include "Sgl/Common.h"

#include <functional>
#include <array>

namespace sgl
{
	GenericWindow::GenericWindow(unsigned int width, unsigned int height, const char* title)
		: props{ width, height, title }, vSyncOn(true), fullScreen{ 0, 0, false } {}

	GenericWindow::~GenericWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	Window* Window::Create(unsigned int width, unsigned int height, const char* title)
	{
		auto window = new GenericWindow(width, height, title);
		if (window->InitWindow() == -1) {
			delete window;
			return nullptr;
		}
		return window;
	}

	bool GenericWindow::IsClosed() const
	{
		return glfwWindowShouldClose(window);
	}

	void GenericWindow::Clear() const
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GenericWindow::Update() const
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void GenericWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		vSyncOn = enabled;
	}

	void GenericWindow::SetEventCallback(EventCallbackFn fn)
	{
		eventCallbackFn = fn;
	}

	void GenericWindow::ToggleFullScreen()
	{
		auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		if (fullScreen.on) {
			glfwSetWindowMonitor(window, NULL, fullScreen.windowedPosX, fullScreen.windowedPosY, props.width, props.height, GLFW_DONT_CARE);
		}
		else {
			glfwGetWindowPos(window, &fullScreen.windowedPosX, &fullScreen.windowedPosY);
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
		}

		fullScreen.on = !fullScreen.on;
	}

	int GenericWindow::InitWindow()
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

		/* Mouse Events */
		/*glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);
			MouseMoved e(xPos, win.windowHeight - yPos); // Makes the origin in the bottom left
			win.eventCallbackFn(e);
		});*/

		glfwSetDropCallback(window, [](GLFWwindow* window, int count, const char** paths) {
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);
			win.eventCallbackFn(new DropEvent(count, paths));
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				win.eventCallbackFn(new MouseButtonPressed(button));
				break;
			}
			case GLFW_RELEASE: {
				win.eventCallbackFn(new MouseButtonReleased(button));
				break;
			}
			}
		});
		/* Key Events */
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {

				/* Fullscreen (Alt-Enter) */
				if (key == GLFW_KEY_ENTER && Input::IsKeyPressed(GLFW_KEY_LEFT_ALT))
					win.ToggleFullScreen();

				win.eventCallbackFn(new KeyPressedEvent(key, 0));
				break;
			}
			case GLFW_RELEASE: {
				win.eventCallbackFn(new KeyReleasedEvent(key));
				break;
			}
			case GLFW_REPEAT: {
				win.eventCallbackFn(new KeyPressedEvent(key, 1));
				break;
			}
			}
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);
			win.eventCallbackFn(new WindowCloseEvent);
		});

		/* Initialize OpenGL for desktop or embedded */
		#ifndef USE_EMSCRIPTEN
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			SglCoreError("Failed to initialize Glad");
			return -1;
		}
		#endif

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		// glEnable(GL_MULTISAMPLE); Only in core

		return 1;
	}
}
