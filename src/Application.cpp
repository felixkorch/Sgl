#include "Sgl/OpenGL.h"
#include "Sgl/Log.h"
#include "Sgl/Application.h"
#include "Sgl/LayerStack.h"
#include "Sgl/Window.h"
#include "Sgl/Events/Event.h"
#include "Sgl/Events/ApplicationEvent.h"
#include "GLFW/glfw3.h"

namespace sgl
{
	#ifdef PLATFORM_WEB

	static void CallMain(void* fp)
	{
		std::function<void()>* fn = (std::function<void()>*) fp;
		(*fn)();
	}
	#endif

	Application* Application::sInstance = nullptr;

	Application::Application(WindowProperties props)
		: layerstack(new LayerStack)
	{
		SGL_ASSERT(sInstance == nullptr, "Application already exists!");
		sInstance = this;
		window = Window::Create(props);
		if (!window) {
			running = false;
			return;
		}
		window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		Log::Init();
		SGL_CORE_INFO("Sucessfully initialized the app!");

        imGuiLayer = new ImGuiLayer;
        PushOverlay(imGuiLayer);
	}

	Application::~Application()
	{
		delete layerstack;
		if(window) delete window;
	}

	void Application::PushLayer(Layer* layer)
	{
		layerstack->PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		layerstack->PushOverlay(overlay);
		overlay->OnAttach();
	}

    void Application::PopLayer(Layer* layer)
    {
        layerstack->PopLayer(layer);
        layer->OnDetach();
    }

    void Application::PopOverlay(Layer* overlay)
    {
        layerstack->PopOverlay(overlay);
        overlay->OnDetach();
    }

    void Application::OnEvent(Event* e)
	{
		// Add to event queue
		eventQueue.PushEvent(e);
	}

	bool Application::OnWindowClose(Event* e)
	{
		running = false;
		return true;
	}

	void Application::Run()
	{
		#ifdef PLATFORM_WEB
		std::function<void()> mainLoop = [&]() {
		#else
		while (running) {
		#endif

			window->Clear();

			// Event Loop
			ProcessEvents();

			// Update
			for (auto layer : layerstack->GetLayers())
				layer->OnUpdate();

            imGuiLayer->Begin();
            for (auto layer : layerstack->GetLayers())
                layer->OnImGuiRender();
            imGuiLayer->End();

			window->Update();

		#ifdef PLATFORM_WEB
		};
		emscripten_set_main_loop_arg(CallMain, &mainLoop, 0, 1);
		#else
		}
		#endif
	}
	
	void Application::ProcessEvents()
	{
		Event* e = eventQueue.GetNext();
        auto layers = layerstack->GetLayers();
		while (e) {
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<WindowCloseEvent>(SGL_BIND_EVENT(Application::OnWindowClose));
            for (auto it = layers.end(); it != layers.begin();) {
				(*--it)->OnEvent(*e);
				if (e->handled)
					break;
			}
			eventQueue.Pop();
			e = eventQueue.GetNext();
		}
	}


}
