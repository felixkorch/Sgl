#pragma once
#include "Sgl/LayerStack.h"
#include "Sgl/Window.h"
#include "Sgl/Events/Event.h"
#include "Sgl/Events/EventQueue.h"
#include "Sgl/ImGuiLayer.h"

namespace sgl
{
	class Application {
		static Application* sInstance;
	protected:
		Window* window;
		LayerStack* layerstack;
        ImGuiLayer* imGuiLayer;
		EventQueue eventQueue;
		bool running = true;
	public:
		Application(WindowProperties props);
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		void OnEvent(Event* e);
		bool OnWindowClose(Event* e);
		void Run();
		Window* GetWindow() { return window; }
		static Application& Get() { return *sInstance; }
	private:
		void ProcessEvents();
	};

	// To be defined in client.
	Application* CreateApplication();
}
