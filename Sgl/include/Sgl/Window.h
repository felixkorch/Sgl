#pragma once
#include "Sgl/Common.h"
#include "Sgl/Events/Event.h"

#include <functional>

namespace sgl
{
	class Window {
	protected:
		GLFWwindow* window;
		unsigned int windowWidth;
		unsigned int windowHeight;
		const char* title;
		bool vSyncOn = false;

		using EventCallbackFn = std::function<void(Event&)>;
		EventCallbackFn eventCallbackFn;
	public:
		Window(unsigned int width, unsigned int height, const char* title);
		~Window();

		bool IsClosed() const;
		void Clear() const;
		void Update() const;
		void SetVSync(bool enabled);
		static Window* Create(unsigned int width, unsigned int height, const char* title);
		void SetEventCallback(EventCallbackFn fn);

	private:
		int InitWindow();
	};
}