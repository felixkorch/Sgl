#pragma once
#include "Sgl/Application.h"
#include <functional>

extern sgl::Application* sgl::CreateApplication();


int main()
{
	auto app = sgl::CreateApplication();
	app->Run();
	delete app;
	return 0;
}