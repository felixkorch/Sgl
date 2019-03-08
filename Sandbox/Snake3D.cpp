#include "Sgl/Entrypoint.h"
#include "Snake3D.h"

using namespace sgl;

class Sample : public Layer {
private:
	Snake3D snake3d;
public:
	Sample()
		: Layer("GameLayer") {}

	void OnUpdate() override
	{
		snake3d.Update();
	}

	void OnEvent(Event& event) override
	{
		
	}
};

class Sandbox : public Application {
public:

	Sandbox()
		: Application(1280, 720, "Snake")
	{
		PushLayer(new Sample());
	}

	~Sandbox() {}

};

sgl::Application* sgl::CreateApplication()
{
	return new Sandbox;
}