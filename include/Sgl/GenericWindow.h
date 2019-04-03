#pragma once
#include "Sgl/Window.h"
#include "GLFW/glfw3.h"

namespace sgl
{
	class GenericWindow : public Window {
	protected:
		GLFWwindow* window;
		bool vSyncOn;
		bool fullScreen;
		int windowedXPos;
		int windowedYPos;

		int framesPerSecond;
		int nbFrames;
		double fpsCounter;
		double delayCounter;

	public:

		GenericWindow(WindowProperties props);
		~GenericWindow();

		virtual bool IsClosed() const override;
		virtual void Clear() override;
		virtual void Update() override;
		virtual void SetVSync(bool enabled) override;
		virtual void ToggleFullScreen() override;
		virtual bool IsVSync() override;
		virtual void SetFPS(int fps) override;
		virtual bool IsFullScreen() override;

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

	private:
		void MeasureFPS(int& nbFrames, double& lastTime);
	};
}