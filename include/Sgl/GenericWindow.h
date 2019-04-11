#pragma once
#include "Sgl/Window.h"
#include "GLFW/glfw3.h"

#include <chrono>

namespace sgl
{
	class GenericWindow : public Window {
	protected:
		GLFWwindow* window;
		bool vSyncOn;
		bool fullScreen;
		int windowedXPos;
		int windowedYPos;

        // Used to force a specific FPS
        std::chrono::steady_clock::time_point delay;
		int framesPerSecond;

        // Used to keep track of FPS to print to the console
		int nbFrames;
		double fpsCounter;

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