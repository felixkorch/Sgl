#pragma once
#include "Sgl/Window.h"
#include "GLFW/glfw3.h"

namespace sgl
{
	class GenericWindow : public Window {
	private:
		GLFWwindow* window;
		WindowProperties props;
		bool vSyncOn;
	public:
		GenericWindow(unsigned int width, unsigned int height, const char* title);
		~GenericWindow();

		virtual bool IsClosed() const override;
		virtual void Clear() const override;
		virtual void Update() const override;
		virtual void SetVSync(bool enabled) override;
		virtual void SetEventCallback(EventCallbackFn fn) override;

		virtual void* GetNativeWindow() const override
		{
			return window;
		}

		unsigned int GetWindowWidth()
		{
			return props.width;
		}

		unsigned int GetWindowHeight()
		{
			return props.height;
		}

		int InitWindow();
	};
}