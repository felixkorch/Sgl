#pragma once
#include "Sgl/Window.h"
#include "GLFW/glfw3.h"

// Nessescary to debug emscripten stuff
#ifdef _MSC_VER
#include "C:/Users/korch/Documents/emsdk-master/emscripten/1.38.28/system/include/emscripten/emscripten.h"
#include "C:/Users/korch/Documents/emsdk-master/emscripten/1.38.28/system/include/emscripten/html5.h"
#endif

namespace sgl
{
	// Hack to deal with emscriptens raw C pointers, declared as a friend to access private members
	static int EmscriptenResizeCallback(int eventType, const EmscriptenFullscreenChangeEvent* fullscreenChangeEvent, void* data);

	class WebWindow : public Window {
	private:
		int fullScreenWidth;
		int fullScreenHeight;
	protected:
		GLFWwindow* window;
		bool vSyncOn;
		bool fullScreen;

		int framesPerSecond;
		int nbFrames;
		double fpsCounter;
		double delayCounter;
	public:

		WebWindow(WindowProperties props);
		~WebWindow();

		virtual bool IsClosed() const override;
		virtual void Clear() override;
		virtual void SetFPS(int fps) override;
		virtual void Update() override;
		virtual void SetVSync(bool enabled) override;
		virtual void ToggleFullScreen() override;
		virtual bool IsVSync() override;
		virtual bool IsFullScreen() override;

		virtual void* GetNativeWindow() const override
		{
			return window;
		}

		virtual int GetWindowWidth() override
		{
			if (fullScreen)
				return fullScreenWidth;
			return props.width;
		}

		virtual int GetWindowHeight() override
		{
			if (fullScreen)
				return fullScreenHeight;
			return props.height;
		}

		int Init();

	private:
		friend int EmscriptenResizeCallback(int eventType, const EmscriptenFullscreenChangeEvent* fullscreenChangeEvent, void* data);
		void ToggleSoftFullScreen();
		void ToggleStandardFullScreen();
		void MeasureFPS(int& nbFrames, double& lastTime);
	};
}