#include "Sgl/Common.h"
#include "Sgl/Application.h"
#include "Sgl/LayerStack.h"
#include "Sgl/Window.h"
#include "Sgl/Events/Event.h"
#include "Sgl/Events/ApplicationEvent.h"
#include "Sgl/Log.h"

namespace sgl
{
	#ifdef USE_EMSCRIPTEN

	static void CallMain(void* fp)
	{
		std::function<void()>* fn = (std::function<void()>*) fp;
		(*fn)();
	}
	#endif

	Application::Application(unsigned int width, unsigned int height, const char* title)
	{
		window = Window::Create(width, height, title);
		window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		Log::Init();
		SglInfo("Sucessfully initialized the app!");
	}

	Application::~Application()
	{
		delete window;
	}

	void Application::PushLayer(Layer* layer)
	{
		layerstack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		layerstack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = layerstack.end(); it != layerstack.begin();) {
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	bool Application::OnWindowClose(Event& e)
	{
		running = false;
		return true;
	}

	void Application::Run()
	{

		#ifdef USE_EMSCRIPTEN
		std::function<void()> mainLoop = [&]() {
			#else
		while (running) {
			#endif
			window->Clear();
			for (Layer* l : layerstack) {
				l->OnUpdate();
			}
			window->Update();
			#ifdef USE_EMSCRIPTEN
		};
		emscripten_set_main_loop_arg(CallMain, &mainLoop, 0, 1);
		#else
		}
		#endif
	}

}