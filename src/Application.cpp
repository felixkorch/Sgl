#include "Sgl/OpenGL.h"
#include "Sgl/Common.h"
#include "Sgl/Application.h"
#include "Sgl/LayerStack.h"
#include "Sgl/Window.h"
#include "Sgl/Events/Event.h"
#include "Sgl/Events/ApplicationEvent.h"
#include "GLFW/glfw3.h"

namespace sgl
{
	#ifdef USE_EMSCRIPTEN

	static void CallMain(void* fp)
	{
		std::function<void()>* fn = (std::function<void()>*) fp;
		(*fn)();
	}
	#endif

	Application* Application::sInstance = nullptr;

	Application::Application(unsigned int width, unsigned int height, const char* title)
	{
		SglAssert(sInstance == nullptr, "Application already exists!");
		sInstance = this;
		window = Window::Create(width, height, title);
		if (!window) {
			running = false;
			return;
		}
		window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		Log::Init();
		SglCoreInfo("Sucessfully initialized the app!");
	}

	Application::~Application()
	{
		if(window) delete window;
	}

	void Application::PushLayer(Layer* layer)
	{
		layerstack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		overlay->OnAttach();
		layerstack.PushOverlay(overlay);
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
		double lastTime = glfwGetTime();
		int nbFrames = 0;

		#ifdef USE_EMSCRIPTEN
		std::function<void()> mainLoop = [&]() {
			#else
		while (running) {
			#endif

			/* Mesaure FPS */
			double currentTime = glfwGetTime();
			nbFrames++;
			if (currentTime - lastTime >= 1.0) { // If last print was more than 1 sec ago
				// Print and reset timer
				auto time = 1000.0 / double(nbFrames);
				SglCoreTrace("{} ms/frame ({} FPS)", time, 1000 * (1 / time));
				nbFrames = 0;
				lastTime += 1.0;
			}

			window->Clear();

			/* Event loop */
			Event* e = eventQueue.GetNext();
			while (e) {
				EventDispatcher dispatcher(e);
				dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
				for (auto it = layerstack.end(); it != layerstack.begin();) {
					(*--it)->OnEvent(*e);
					if (e->handled)
						break;
				}
				eventQueue.Pop();
				e = eventQueue.GetNext();
			}

			/* Update */
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