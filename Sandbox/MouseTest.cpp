#include "Sgl/Entrypoint.h"
#include "Sgl/Sgl2D.h"

#ifdef USE_EMSCRIPTEN
#define SHADER(x) x ".gles.shader"
#else
#define SHADER(x) x ".shader"
#endif

using namespace sgl;

class TestLayer : public Layer {
private:
	BatchRendererGLES2* renderer;
	Shader* shader;

	Renderable2D rect;
	glm::vec2 mousePos;
	bool movingRect = false;
public:
	TestLayer()
		: Layer("GameLayer")
	{
		shader = new Shader("res/shaders/" SHADER("2D"));
		renderer = new BatchRendererGLES2(1280, 720, *shader);
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
			ClientTrace(c.ToString());
			if (rect.bounds.Contains(mousePos))
				movingRect = true;
		}
		else if (event.GetEventType() == EventType::MouseButtonReleased) {
			MouseButtonReleased c = (MouseButtonReleased&)event;
			ClientTrace(c.ToString());
			movingRect = false;
		}
		else if (event.GetEventType() == EventType::CursorMoved) {
			CursorEvent c = (CursorEvent&)event;
			mousePos.x = c.GetXPos();
			mousePos.y = 720 - c.GetYPos();
		}
	}
};

class MouseTest : public Application {
public:

	MouseTest()
		: Application(1280, 720, "Sandbox")
	{
		PushLayer(new TestLayer());
	}

	~MouseTest() {}

};

sgl::Application* sgl::CreateApplication()
{
	return new MouseTest;
}
