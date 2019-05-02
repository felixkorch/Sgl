#pragma once
#include "Sgl/LayerStack.h"
#include "Sgl/Window.h"
#include "Sgl/Events/Event.h"
#include "Sgl/Events/EventQueue.h"
#include "Sgl/ImGui/ImGuiLayer.h"

namespace sgl
{
	class Application {
		static Application* sInstance;
	protected:
		Window* window;
		LayerStack* layerStack;
        ImGuiLayer* imGuiLayer;
		EventQueue eventQueue;
		bool running;
	public:
		Application(WindowProperties props);
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		void OnEvent(Event* e);
		void Run();
		Window* GetWindow() { return window; }
		static Application& Get() { return *sInstance; }
	private:
		void ProcessEvents();
		bool OnWindowClose(Event& e);
	};

	// To be defined in client.
	Application* CreateApplication();
}
