/*
#include "Sgl/Entrypoint.h"
#include "Sgl/Graphics/ForwardRenderer.h"
#include "Sgl/Graphics/Camera.h"
#include "Sgl/Graphics/Material.h"
#include "Sgl/Graphics/Mesh.h"
#include "Sgl/Graphics/Light.h"
#include "Sgl/Graphics/Model.h"
#include "Sgl/Graphics/Texture.h"
#include "Sgl/Input.h"
#include "Sgl/Events/KeyCodes.h"

#include "Snake3D.h"

using namespace sgl;

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define DegreesToRadians(x) x*(3.141592f/180.0f)

class Sample : public Layer {
private:
	ForwardRenderer* renderer;
	Model* model;
	Shader* shader;
	Camera* camera;
	Material* material;
	std::shared_ptr<Mesh> cube;
public:
	Sample()
		: Layer("GameLayer")
	{
		camera = new Camera(
			glm::vec3(0, 5, -7),
			DegreesToRadians(60.0f),
			static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT),
			0.1f,
			100.0f);

		renderer = new ForwardRenderer;
		renderer->Begin(*camera);

		shader = new Shader("res/shaders/Lamp.shader");

		material = new Material(*shader);

		/ *material.SetLightingData(
			LightingData{
				glm::vec3(1.0, 1.0, 1.0),
				glm::vec3(1.0, 1.0, 1.0),
				glm::vec3(1.0, 1.0, 1.0),
				32.0f
			});* /

		cube = std::make_shared<Mesh>("res/smallercube.obj", *material);
		model = new Model(cube);
		//model->GetTransform().translate = light->position;
	}

	void OnUpdate() override
	{
		renderer->Clear();
		renderer->Submit(*model);
		renderer->Render();
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
}*/