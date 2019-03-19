#include <Sgl.h>
#include <ctime>

#ifdef USE_EMSCRIPTEN
#define VertexShader   Shader::GLES2_Vertex_Shader2D
#define FragmentShader Shader::GLES2_Fragment_Shader2D
#else
#define VertexShader   Shader::Core_Vertex_Shader2D
#define FragmentShader Shader::Core_Fragment_Shader2D
#endif


using namespace sgl;

class TestLayer : public Layer {
private:
	Renderer2D* renderer;
	Shader shader;
	Renderable2D rect;
	Texture2D* tex;
	glm::vec2 offset;
	bool movingRect = false;
public:
	TestLayer()
		: Layer("GameLayer"), shader(VertexShader, FragmentShader)
	{
		renderer = Renderer2D::Create(1280, 720, shader);
		rect = Renderable2D(glm::vec2(200, 200), glm::vec2(200, 200));
		rect.color = glm::vec4(0.5, 0.2, 0.3, 1.0);
		tex = new Texture2D("res/tile.png");

		srand(time(nullptr));
	}

	~TestLayer()
	{
		delete renderer;
		delete tex;
	}

	void OnUpdate() override
	{
		auto mousePos = Input::GetMousePosition();
		if (movingRect)
			rect.SetPos(glm::vec2(mousePos.first - offset.x, mousePos.second - offset.y));

		for (int i = 0; i < 10; i++) {
			if (Input::IsJoystickButtonPressed(i, SGL_JOYSTICK_1))
				SglTrace("Button {} pressed!", i);
		}

		auto axis = Input::GetJoystickAxis(SGL_JOYSTICK_1);
		if (!axis.empty()) {
			rect.bounds.pos.x += axis[0];
			rect.bounds.pos.y -= axis[1];
		}

		renderer->Begin();

		renderer->Submit(rect);
		renderer->SubmitTexture(tex);

		renderer->End();
		renderer->Flush();
	}

	void OnEvent(Event& event) override
	{
		if (event.GetEventType() == EventType::MouseButtonPressed) {
			auto& c = (MouseButtonPressed&)event;
			SglTrace(c.ToString());
			auto mousePos = Input::GetMousePosition();
			if (rect.bounds.Contains(glm::vec2(mousePos.first, mousePos.second))) {
				movingRect = true;
				offset = glm::vec2(mousePos.first - rect.bounds.MinBounds().x, mousePos.second - rect.bounds.MinBounds().y);
			}
			if (c.GetButton() == SGL_MOUSE_BUTTON_RIGHT)
				rect.color = RandColor();
		}
		else if (event.GetEventType() == EventType::MouseButtonReleased) {
			auto& c = (MouseButtonReleased&)event;
			SglTrace(c.ToString());
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
