#include "Sgl/Entrypoint.h"
#include "Sgl/Sgl.h"

#include <iostream>

#ifdef USE_EMSCRIPTEN
#define Shader(x) x ".gles.shader"
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
		renderer = new BatchRenderer(1280, 720, shader);

		/* r1 */
		glm::vec4 color(0.7, 0.3, 0.2, 1.0);
		VertexData v1{ glm::vec3(0, 0, 0), color };
		VertexData v2{ glm::vec3(250, 0, 0), color };
		VertexData v3{ glm::vec3(250, 250, 0), color };
		VertexData v4{ glm::vec3(0, 250, 0), color };

		/* r2 */
		glm::vec4 color2(0.6, 0.2, 0.15, 1.0);
		VertexData z1{ glm::vec3(500, 500, 0), color2 };
		VertexData z2{ glm::vec3(700, 500, 0), color2 };
		VertexData z3{ glm::vec3(700, 700, 0), color2 };
		VertexData z4{ glm::vec3(500, 700, 0), color2 };

		r1 = Renderable2D(v1, v2, v3, v4);
		r2 = Renderable2D(z1, z2, z2, z4);
	}

	void OnUpdate() override
	{
		renderer->Begin();

		renderer->Submit(r1);
		renderer->Submit(r2);

		if (input::IsKeyPressed(GLFW_KEY_RIGHT)) {
			r1.TranslateX(1);
		}
		else if (input::IsKeyPressed(GLFW_KEY_LEFT)) {
			r1.TranslateX(-1);
		}
		else if (input::IsKeyPressed(GLFW_KEY_UP)) {
			r1.TranslateY(1);
		}
		else if (input::IsKeyPressed(GLFW_KEY_DOWN)) {
			r1.TranslateY(-1);
		}
		else if (input::IsKeyPressed(GLFW_KEY_A)) {
			renderer->MoveCamera(glm::vec2(-1, 0));
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
		: Application(1280, 720, "Sandbox")
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}

};

sgl::Application* sgl::CreateApplication()
{
	return new Sandbox;
}