#pragma once
#include "Sgl/Application.h"
#include <functional>

extern sgl::Application* sgl::CreateApplication();
/*
#ifdef USE_EMSCRIPTEN

static void CallMain(void* fp)
{
	std::function<void()>* fn = (std::function<void()>*) fp;
	(*fn)();
}

#endif*/


int main()
{
	auto app = sgl::CreateApplication();
	/*#ifdef USE_EMSCRIPTEN
	std::function<void()> mainLoop = [&]() {
		app->Run();
	};
	emscripten_set_main_loop_arg(CallMain, &mainLoop, 0, 1);
	#else*/
	app->Run();
	//#endif
	delete app;
	return 0;
}