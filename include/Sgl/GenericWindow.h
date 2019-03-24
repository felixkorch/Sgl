#pragma once
#include "Sgl/Window.h"
#include "GLFW/glfw3.h"

namespace sgl
{
	class GenericWindow : public Window {
	protected:
		GLFWwindow* window;
		WindowProperties props;
		bool vSyncOn;
		bool fullScreen;
		int windowedXPos;
		int windowedYPos;

	public:

		GenericWindow(int width, int height, const char* title);
		~GenericWindow();

		virtual bool IsClosed() const override;
		virtual void Clear() const override;
		virtual void Update() const override;
		virtual void SetVSync(bool enabled) override;
		virtual void ToggleFullScreen() override;

		virtual void* GetNativeWindow() const override
		{
			return window;
		}

		virtual int GetWindowWidth() override
		{
			if (fullScreen) {
				auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
				return mode->width;
			}
			return props.width;
		}

		virtual int GetWindowHeight() override
		{
			if (fullScreen) {
				auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
				return mode->height;
			}
			return props.height;
		}

		virtual int Init();
	};
}