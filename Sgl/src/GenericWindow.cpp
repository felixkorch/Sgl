#include "Sgl/OpenGL.h"
#include "GLFW/glfw3.h"
#include "Sgl/GenericWindow.h"
#include "Sgl/Events/KeyEvent.h"
#include "Sgl/Events/ApplicationEvent.h"
#include "Sgl/Events/MouseEvent.h"
#include "Sgl/Input.h"

#include <functional>
#include <array>

namespace sgl
{
	GenericWindow::GenericWindow(unsigned int width, unsigned int height, const char* title)
		: windowWidth(width), windowHeight(height), title(title)
	{
		InitWindow();
	}

	GenericWindow::~GenericWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	Window* Window::Create(unsigned int width, unsigned int height, const char* title)
	{
		return new GenericWindow(width, height, title);
	}

	bool GenericWindow::IsClosed() const
	{
		return glfwWindowShouldClose(window);
	}

	void GenericWindow::Clear() const
	{
		glClearColor(0.1, 0.1, 0.1, 1);
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


	int GenericWindow::InitWindow()
	{
		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		SetVSync(true);

		window = glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);
		if (!window) {
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);

		/* Mouse Events */
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);
			CursorEvent e(xPos, yPos);
			win.eventCallbackFn(e);
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressed e(button);
				win.eventCallbackFn(e);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleased e(button);
				win.eventCallbackFn(e);
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
				/*if (key == GLFW_KEY_ENTER && Input::IsKeyPressed(GLFW_KEY_LEFT_ALT)) {
					auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
					glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, 0);
				}*/

				KeyPressedEvent e(key, 0);
				win.eventCallbackFn(e);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent e(key);
				win.eventCallbackFn(e);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent e(key, 1);
				win.eventCallbackFn(e);
				break;
			}
			}

			Input::GetKeys()[key] = action != GLFW_RELEASE; // Temporary key pressed -polling solution
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			GenericWindow& win = *(GenericWindow*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			win.eventCallbackFn(e);
		});

		/* Initialize OpenGL for desktop or embedded */
		int status = 1;
		#ifndef USE_EMSCRIPTEN
		status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		#endif
		SglAssert(status, "Failed to initialize Glad.");

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		// glEnable(GL_MULTISAMPLE); Only in core

		return 1;
	}
}