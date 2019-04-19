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

        // Used to force a specific FPS
        std::chrono::steady_clock::time_point delay;
        int framesPerSecond;

        // Used to keep track of FPS to print to the console
        int frames;
        double frameDelay;
	public:

		WebWindow(WindowProperties props);
		~WebWindow();

		virtual bool IsClosed() const override;
		virtual void SetFPS(int fps) override;
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
			if (fullScreen)
				return fullScreenWidth;
			return props.width;
		}

		virtual int GetHeight() override
		{
			if (fullScreen)
				return fullScreenHeight;
			return props.height;
		}

		int TryInit();

    protected:
		virtual void Clear() override;
		virtual void Update() override;

	private:
		friend int EmscriptenResizeCallback(int eventType, const EmscriptenFullscreenChangeEvent* fullscreenChangeEvent, void* data);
		void SetStandardFullscreen();
		void SetSoftFullscreen();
		void ExitStandardFullscreen();
		void ExitSoftFullscreen();
		void DebugPrintFPS(int& nbFrames, double& lastTime);
	};
}