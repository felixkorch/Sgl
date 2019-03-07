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

#include "snake3d.h"

using namespace sgl;

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define degreesToRadians(x) x*(3.141592f/180.0f)

class Sample : public Layer {
private:
	ForwardRenderer* renderer;
	Snake3D* snake3d;
	Light* light;
	Model* lampModel;
	Model* terrainModel;
	Shader* lampShader;
	Camera* camera;
	std::shared_ptr<Mesh> lampCube;
public:
	Sample()
		: Layer("GameLayer")
	{
		camera = new Camera(glm::vec3(0, 5, -7), degreesToRadians(60.0f), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.1f, 100.0f);

		light = new Light{
			glm::vec3(0.0f, 5.0f, -5.0f),
			0.3f * glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			0.5f * glm::vec3(1.0f, 1.0f, 1.0f)
		};

		Shader lightShader("res/shaders/Light.shader");
		Material snakeMaterial(lightShader);
		snakeMaterial.Bind();

		snakeMaterial.SetLightingData({
			0.6f * glm::vec3(0.1, 0.9, 0.1),
			0.65f * glm::vec3(0.1, 0.9, 0.1),
			glm::vec3(0.1, 0.9, 0.1),
			32.0f
		});

		Texture white("res/white.png");
		snakeMaterial.SetTexture(white);
		snake3d = new Snake3D(snakeMaterial);

		renderer = new ForwardRenderer;
		renderer->Begin(*camera);
		renderer->SubmitLight(*light);

		const unsigned int tiles = 20;

		Vertex vertices[tiles * tiles];

		for (unsigned int i = 0; i < tiles; i++) {
			for (unsigned int j = 0; j < tiles; j++) {
				vertices[i * tiles + j] = {
						glm::vec3(0.18f - 0.36f * j, -0.18, -0.18f + 0.36f * i),
						glm::vec3(0, 1, 0),
						glm::vec2(0.5f * j, 0.5f * i)
				};
			}
		}

		unsigned int indices[(tiles - 1) * (tiles - 1) * 6];

		for (unsigned int v = 0; v < (tiles - 1); v++) {
			unsigned int r = 0;
			for (unsigned int i = 0; i < (tiles - 1); i++) {

				indices[r + ((tiles - 1) * 6 * v)] = i + tiles * v;
				indices[r + 1 + ((tiles - 1) * 6 * v)] = i + 1 + tiles * v;
				indices[r + 2 + ((tiles - 1) * 6 * v)] = tiles * (v + 1) + i + 1;
				indices[r + 3 + ((tiles - 1) * 6 * v)] = tiles * (v + 1) + i + 1;
				indices[r + 4 + ((tiles - 1) * 6 * v)] = tiles * (v + 1) + i;
				indices[r + 5 + ((tiles - 1) * 6 * v)] = i + tiles * v;

				r += 6;
			}
		}

		Material terrainMaterial(lightShader);
		terrainMaterial.SetLightingData({ 0.4f * glm::vec3(1.0, 1.0, 1.0),
										  0.5f * glm::vec3(1.0, 1.0, 1.0),
										  1.0f * glm::vec3(1.0, 1.0, 1.0),
										  1.0f
									    });

		Texture tex("res/tile.png");
		terrainMaterial.SetTexture(tex);
		std::shared_ptr<Mesh> terrain = std::make_shared<Mesh>(vertices, tiles * tiles, indices, (tiles - 1) * (tiles - 1) * 6, terrainMaterial);
		terrainModel = new Model(terrain);
		terrainModel->GetTransform().translate += glm::vec3(0.36f * 9, 0, -0.36f * 7);

	    lampShader = new Shader("res/shaders/Lamp.shader");
		Material lampMaterial(*lampShader);
		lampCube = std::make_shared<Mesh>("res/smallercube.obj", lampMaterial);
		lampModel = new Model(lampCube);
		lampModel->GetTransform().translate = light->position;
	}

	void OnUpdate() override
	{
		if (Input::IsKeyPressed(SGL_KEY_RIGHT))
			snake3d->setDir(glm::vec3(-1, 0, 0));

		else if (Input::IsKeyPressed(SGL_KEY_LEFT))
			snake3d->setDir(glm::vec3(1, 0, 0));

		else if (Input::IsKeyPressed(SGL_KEY_UP))
			snake3d->setDir(glm::vec3(0, 0, 1));

		else if (Input::IsKeyPressed(SGL_KEY_DOWN))
			snake3d->setDir(glm::vec3(0, 0, -1));

		else if (Input::IsKeyPressed(SGL_KEY_D)) {
			light->position += glm::vec3(-0.1f, 0, 0);
			lampModel->GetTransform().translate = light->position;
		}
		else if (Input::IsKeyPressed(SGL_KEY_A)) {
			light->position += glm::vec3(0.1f, 0, 0);
			lampModel->GetTransform().translate = light->position;
		}
		else if (Input::IsKeyPressed(SGL_KEY_W)) {
			light->position += glm::vec3(0, 0, 0.1f);
			lampModel->GetTransform().translate = light->position;
		}
		else if (Input::IsKeyPressed(SGL_KEY_S)) {
			light->position += glm::vec3(0, 0, -0.1f);
			lampModel->GetTransform().translate = light->position;
		}

		snake3d->update();
		for (Model &m : snake3d->getModels()) {
			renderer->Submit(m);
		}

		renderer->SubmitLight(*light);
		renderer->Submit(*terrainModel);
		renderer->Render();
		renderer->Clear();

		lampShader->Bind();
		lampShader->SetUniformMat4f("u_Proj", camera->GetView() * lampModel->GetModelMatrix());
		lampCube->Draw();
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