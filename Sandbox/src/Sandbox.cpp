#include "Sgl/Entrypoint.h"
#include "Sgl/Sgl2D.h"

#ifdef USE_EMSCRIPTEN
#define Shader(x) x ".gles3.shader"
#else
#define Shader(x) x ".shader"
#endif

using namespace sgl;

class ExampleLayer : public Layer {
private:
	BatchRenderer* renderer;
	Renderable2D r1, r2;
public:
	ExampleLayer()
		: Layer("GameLayer")
	{
		Shader shader("res/shaders/" Shader("2D"));
		renderer = new BatchRenderer(800, 600, shader);

		/* r1 */
		const glm::vec4 color(0.7, 0.3, 0.2, 1.0);
		r1 = Renderable2D::CreateRectangle(glm::vec2(50, 50), glm::vec2(0, 0), color);

		/* r2 */
		const glm::vec4 color2(0.6, 0.2, 0.15, 1.0);
		r2 = Renderable2D::CreateRectangle(glm::vec2(50, 50), glm::vec2(200, 100), color2);
	}

	void OnUpdate() override
	{
		renderer->Begin();

		renderer->Submit(r1);
		renderer->Submit(r2);

		if (Input::IsKeyPressed(GLFW_KEY_RIGHT)) {
			r1.TranslateX(1);
		}
		else if (Input::IsKeyPressed(GLFW_KEY_LEFT)) {
			r1.TranslateX(-1);
		}
		else if (Input::IsKeyPressed(GLFW_KEY_UP)) {
			r1.TranslateY(1);
		}
		else if (Input::IsKeyPressed(GLFW_KEY_DOWN)) {
			r1.TranslateY(-1);
		}
		else if (Input::IsKeyPressed(GLFW_KEY_A)) {
			renderer->MoveCamera(glm::vec2(-1, 0));
		}
		else if (Input::IsKeyPressed(GLFW_KEY_D)) {
			renderer->MoveCamera(glm::vec2(1, 0));
		}

		renderer->End();
		renderer->Flush();
	}

	void OnEvent(Event& event) override
	{
		if (event.GetEventType() == EventType::KeyPressed) {
			KeyPressedEvent k = (KeyPressedEvent&)event;

			switch (k.GetKeyCode()) {
			case GLFW_KEY_RIGHT: {
				std::cout << "Right key pressed!" << std::endl;
				break;
			}
			case GLFW_KEY_LEFT: {
				std::cout << "Left key pressed!" << std::endl;
				break;
			}
			}
		}
	}
};

class Sandbox : public Application {
public:

	Sandbox()
		: Application(800, 600, "Sandbox")
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}

};

sgl::Application* sgl::CreateApplication()
{
	return new Sandbox;
}