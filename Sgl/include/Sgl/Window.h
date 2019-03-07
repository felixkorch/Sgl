#pragma once
#include "Sgl/Events/Event.h"
#include <functional>

namespace sgl
{
	class Window {
	protected:
		using EventCallbackFn = std::function<void(Event&)>;
		EventCallbackFn eventCallbackFn;
	public:

		~Window() {}
		virtual bool IsClosed() const = 0;
		virtual void Clear() const = 0;
		virtual void Update() const = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual void SetEventCallback(EventCallbackFn fn) = 0;

		static Window* Create(unsigned int width, unsigned int height, const char* title);
	};
}