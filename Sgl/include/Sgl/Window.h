#pragma once
#include "Sgl/Events/Event.h"
#include <functional>

namespace sgl
{
	struct WindowProperties {
		unsigned int width;
		unsigned int height;
		const char* title;
	};

	class Window {
	protected:
		using EventCallbackFn = std::function<void(Event*)>;
		EventCallbackFn eventCallbackFn;
	public:
		virtual ~Window() {}
		virtual bool IsClosed() const = 0;
		virtual void Clear() const = 0;
		virtual void Update() const = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual void SetEventCallback(EventCallbackFn fn) = 0;
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(unsigned int width, unsigned int height, const char* title);
	};
}