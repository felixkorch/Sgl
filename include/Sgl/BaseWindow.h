#pragma once
#include "Sgl/Window.h"
#include "GLFW/glfw3.h"

#include <chrono>

namespace sgl
{
	class BaseWindow : public Window {
	protected:
		GLFWwindow* window;
		bool vSyncOn;
		bool fullScreen;
		int windowedXPos;
		int windowedYPos;

	public:

        BaseWindow(WindowProperties props);
		~BaseWindow();

		virtual bool IsClosed() const override;
		virtual void SetVSync(bool enabled) override;
		virtual void SetFullscreen() override;
		virtual void SetWindowed() override;
		virtual bool IsVSync() override;
		virtual bool IsFullScreen() override;

		virtual void* GetNativeWindow() const override
		{
			return window;
		}

		virtual int GetWidth() override
		{
			if (fullScreen) {
				auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
				return mode->width;
			}
			return props.width;
		}

		virtual int GetHeight() override
		{
			if (fullScreen) {
				auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
				return mode->height;
			}
			return props.height;
		}

		int TryInit();

    protected:
        void Clear() override;
        void Update() override;
	};
}