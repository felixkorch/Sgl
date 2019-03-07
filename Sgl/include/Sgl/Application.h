#pragma once
#include "Sgl/LayerStack.h"
#include "Sgl/Window.h"
#include "Sgl/Events/Event.h"

namespace sgl
{
	class Application {
	protected:
		Window* window;
		LayerStack layerstack;
		bool running = true;
	public:
		Application(unsigned int width, unsigned int height, const char* title);
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void OnEvent(Event& e);
		bool OnWindowClose(Event& e);
		void Run();
	};

	// To be defined in client.
	Application* CreateApplication();
}