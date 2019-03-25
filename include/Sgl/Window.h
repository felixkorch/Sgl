#pragma once
#include "Sgl/Events/Event.h"
#include <functional>

namespace sgl
{
	struct WindowProperties {
		int width = 1280;
		int height = 720;
		const char* title = "Default Title";
		bool resizable = false;
	};

	class Window {
	protected:
		using EventCallbackFn = std::function<void(Event*)>;
		EventCallbackFn CallEventHandler;
		WindowProperties props;
	public:
		Window(WindowProperties props) : props(props) {}
		virtual ~Window() {}
		virtual bool IsClosed() const = 0;
		virtual void Clear() const = 0;
		virtual void Update() const = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() = 0;
		virtual void ToggleFullScreen() = 0;
		virtual bool IsFullScreen() = 0;
		virtual int GetWindowWidth() = 0;
		virtual int GetWindowHeight() = 0;
		virtual void* GetNativeWindow() const = 0;

		bool IsResizable()
		{
			return props.resizable;
		}

		void SetEventCallback(EventCallbackFn fn)
		{
			CallEventHandler = fn;
		}

		static Window* Create(WindowProperties props);
	};
}