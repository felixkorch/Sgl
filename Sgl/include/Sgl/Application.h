#pragma once
#include "Sgl/LayerStack.h"
#include "Sgl/Window.h"
#include "Sgl/Events/Event.h"
#include "Sgl/Events/EventQueue.h"

namespace sgl
{
	class Application {
	protected:
		Window* window;
		LayerStack layerstack;
		EventQueue eventQueue;
		bool running = true;
	public:
		Application(unsigned int width, unsigned int height, const char* title);
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void OnEvent(Event* e);
		bool OnWindowClose(Event* e);
		void Run();
		Window* GetWindow() { return window; }
		static Application& Get() { return *sInstance; }
	private:
		static Application* sInstance;
	};

	// To be defined in client.
	Application* CreateApplication();
}