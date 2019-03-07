#pragma once
#include "Sgl/Window.h"
#include "GLFW/glfw3.h"

namespace sgl
{
	class GenericWindow : public Window {
	protected:
		unsigned int windowWidth;
		unsigned int windowHeight;
		const char* title;
		bool vSyncOn = false;
	private:
		GLFWwindow* window;
	public:
		GenericWindow(unsigned int width, unsigned int height, const char* title);
		~GenericWindow();

		bool IsClosed() const override;
		void Clear() const override;
		void Update() const override;
		void SetVSync(bool enabled) override;
		void SetEventCallback(EventCallbackFn fn) override;
	private:
		int InitWindow();
	};
}