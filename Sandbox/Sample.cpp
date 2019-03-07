/*
#include "Sgl/Entrypoint.h"
#include "Sgl/Sgl2D.h"

#ifdef USE_EMSCRIPTEN
#define Shader(x) x ".gles3.shader"
#else
#define Shader(x) x ".shader"
#endif

using namespace sgl;



class Sample : public Layer {
private:
public:
	Sample()
		: Layer("GameLayer")
	{
	}

	void OnUpdate() override
	{
		
	}

	void OnEvent(Event& event) override
	{
		
	}
};

class Sandbox : public Application {
public:

	Sandbox()
		: Application(1280, 720, "Sandbox")
	{
		PushLayer(new Sample());
	}

	~Sandbox() {}

};

sgl::Application* sgl::CreateApplication()
{
	return new Sandbox;
}*/