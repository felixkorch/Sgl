#include "Sgl/OpenGL.h"
#include "Sgl/Log.h"
#include "Sgl/Application.h"
#include "Sgl/LayerStack.h"
#include "Sgl/Window.h"
#include "Sgl/Events/Event.h"
#include "Sgl/Events/ApplicationEvent.h"

namespace sgl
{
	#ifdef SGL_PLATFORM_WEB

	static void CallMain(void* fp)
	{
		std::function<void()>* fn = (std::function<void()>*) fp;
		(*fn)();
	}
	#endif

	Application* Application::sInstance = nullptr;

	Application::Application(WindowProperties props)
        : window(nullptr)
        , layerStack(new LayerStack)
        , imGuiLayer(nullptr)
        , eventQueue()
        , running(true)
	{
		SGL_ASSERT(sInstance == nullptr, "Application already exists!");
		sInstance = this;
		window = Window::Create(props);
		if (!window) {
			running = false;
			return;
		}
		window->SetEventCallback(SGL_BIND(Application::OnEvent));
		Log::Init();
		SGL_CORE_INFO("Sucessfully initialized the app!");

        imGuiLayer = new ImGuiLayer;
        PushOverlay(imGuiLayer);
	}

	Application::~Application()
	{
        delete layerStack;
		if(window) delete window;
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack->PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		layerStack->PushOverlay(overlay);
	}

    void Application::PopLayer(Layer* layer)
    {
        layerStack->PopLayer(layer);
    }

    void Application::PopOverlay(Layer* overlay)
    {
        layerStack->PopOverlay(overlay);
    }

    void Application::OnEvent(Event* e)
	{
		// Add to event queue
		eventQueue.PushEvent(e);
	}

	bool Application::OnWindowClose(Event& e)
	{
		running = false;
		return true;
	}

	void Application::Run()
	{
		#ifdef SGL_PLATFORM_WEB
		std::function<void()> mainLoop = [&]() {
		#else
		while (running) {
		#endif

			window->Clear();

			// Event Loop
			ProcessEvents();

			// Update
			for (Layer* layer : *layerStack)
				layer->OnUpdate();

            imGuiLayer->Begin();
            for (Layer* layer : *layerStack)
                layer->OnImGuiRender();
            imGuiLayer->End();

			window->Update();

		#ifdef SGL_PLATFORM_WEB
		};
		emscripten_set_main_loop_arg(CallMain, &mainLoop, 0, 1);
		#else
		}
		#endif
	}
	
	void Application::ProcessEvents()
	{
		Event* e = eventQueue.GetNext();
		while (e) {
			EventDispatcher dispatcher(*e);
			dispatcher.Dispatch<WindowCloseEvent>(SGL_BIND(Application::OnWindowClose));
            for (auto it = layerStack->end(); it != layerStack->begin();) {
				(*--it)->OnEvent(*e);
				if (e->handled)
					break;
			}
			eventQueue.Pop(); // Deletes the event
			e = eventQueue.GetNext();
		}
	}


}
