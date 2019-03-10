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
	BatchRenderer* renderer;
	Shader shader;
	Renderable2D rect;
	glm::vec2 offset;
	bool movingRect = false;
public:
	TestLayer()
		: Layer("GameLayer"), shader("res/shaders/" SHADER("2D"))
	{
		renderer = BatchRenderer::MakeBatchRenderer(1280, 720, shader);
		rect = Renderable2D(glm::vec2(200, 200), glm::vec2(200, 200));
		rect.color = glm::vec4(0.5, 0.2, 0.3, 1.0);
		srand(time(nullptr));
	}

	~TestLayer()
	{
		delete renderer;
	}

	void OnUpdate() override
	{
		auto mousePos = Input::GetMousePosition();
		if (movingRect)
			rect.SetPos(glm::vec2(mousePos.first - offset.x, mousePos.second - offset.y));

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
			auto mousePos = Input::GetMousePosition();
			if (rect.bounds.Contains(glm::vec2(mousePos.first, mousePos.second))) {
				movingRect = true;
				offset = glm::vec2(mousePos.first - rect.bounds.MinBounds().x, mousePos.second - rect.bounds.MinBounds().y);
			}
			if (c.GetButton() == 1)
				rect.color = RandColor();
		}
		else if (event.GetEventType() == EventType::MouseButtonReleased) {
			MouseButtonReleased c = (MouseButtonReleased&)event;
			ClientTrace(c.ToString());
			movingRect = false;
		}
	}

private:
	glm::vec4 RandColor()
	{
		return glm::vec4(1 / (float)(rand() % 15), 1 / (float)(rand() % 15), 1 / (float)(rand() % 15), 1.0);
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
