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
	BatchRenderer* renderer;
	Renderable2D rect;
	glm::vec2 mousePos;
	bool movingRect = false;
public:
	Sample()
		: Layer("GameLayer")
	{
		Shader shader("res/shaders/" Shader("2D"));
		renderer = new BatchRenderer(1280, 720, shader);
		rect = Renderable2D(glm::vec2(200, 200), glm::vec2(200, 200));
	}

	void OnUpdate() override
	{
		if (movingRect)
			rect.SetPos(mousePos);

		renderer->Begin();

		renderer->Submit(rect);

		renderer->End();
		renderer->Flush();
	}

	void OnEvent(Event& event) override
	{
		if (event.GetEventType() == EventType::MouseButtonPressed) {
			MouseButtonPressed c = (MouseButtonPressed&)event;
			SglTrace(c.ToString());
			if (rect.bounds.Contains(mousePos))
				movingRect = true;
		}
		else if (event.GetEventType() == EventType::MouseButtonReleased) {
			MouseButtonReleased c = (MouseButtonReleased&)event;
			SglTrace(c.ToString());
			movingRect = false;
		}
		else if (event.GetEventType() == EventType::CursorMoved) {
			CursorEvent c = (CursorEvent&)event;
			mousePos.x = c.GetXPos();
			mousePos.y = 720 - c.GetYPos();
		}
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