#pragma once
#include "Sgl/Graphics/ForwardRenderer.h"
#include "Sgl/Graphics/Camera.h"
#include "Sgl/Graphics/Material.h"
#include "Sgl/Graphics/Mesh.h"
#include "Sgl/Graphics/light.h"
#include "Sgl/Graphics/Model.h"
#include "Sgl/Graphics/Texture.h"
#include "Sgl/Input.h"
#include "Sgl/Events/KeyCodes.h"
#include <vector>
#include <memory>


using namespace sgl;

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define DegreesToRadians(x) x*(3.141592f/180.0f)

#ifndef USE_EMSCRIPTEN
#define SHADER(x) x ".shader"
#else
#define SHADER(x) x ".gles.shader"
#endif

class Snake3D {
private:
	static constexpr auto TILE_SIZE = 0.36f;

	std::size_t ticks = 15;
	glm::vec3 dir;
	std::vector<Model> snakeParts;

	ForwardRenderer* renderer;
	Camera *camera;
	Light *light;
	Model *lampModel, *terrainModel;
	std::shared_ptr<Mesh> cube, snakeCube;
	Material *snakeMaterial, *terrainMaterial, *lampMaterial;
	Shader *simpleShader, *lampShader;
	Texture *white, *tile;

public:
	Snake3D()
	{
		camera = new Camera(
			glm::vec3(0, 5, -7),
			DegreesToRadians(60.0f),
			static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT),
			0.1f,
			100.0f
		);

		light = new Light{
			glm::vec3(0.0f, 5.0f, -5.0f),       // position
			0.3f * glm::vec3(1.0f, 1.0f, 1.0f), // ambient
			glm::vec3(1.0f, 1.0f, 1.0f),        // diffuse 
			0.5f * glm::vec3(1.0f, 1.0f, 1.0f)  // specular
		};

		/* Textures */
		white = new Texture("res/white.png");
		tile = new Texture("res/tile.png");

		simpleShader = new Shader("res/shaders/" SHADER("Simple"));

		snakeMaterial = new Material(*simpleShader);
		snakeMaterial->AddUniform<glm::vec3>("u_Material.ambient", 0.6f * glm::vec3(0.1, 0.9, 0.1));
		snakeMaterial->AddUniform<glm::vec3>("u_Material.diffuse", 0.65f * glm::vec3(0.1, 0.9, 0.1));
		snakeMaterial->AddUniform<glm::vec3>("u_Material.specular", glm::vec3(0.1, 0.9, 0.1));
		snakeMaterial->AddUniform<float>("u_Material.shininess", 32.0f);

		snakeMaterial->Bind();

		snakeMaterial->SetTexture(*white);
		snakeCube = std::make_shared<Mesh>("res/smallercube.obj", *snakeMaterial);

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

		terrainMaterial = new Material(*simpleShader);
		terrainMaterial->AddUniform<glm::vec3>("u_Material.ambient", 0.4f * glm::vec3(1.0, 1.0, 1.0));
		terrainMaterial->AddUniform<glm::vec3>("u_Material.diffuse", 0.4f * glm::vec3(1.0, 1.0, 1.0));
		terrainMaterial->AddUniform<glm::vec3>("u_Material.specular", 0.4f * glm::vec3(1.0, 1.0, 1.0));
		terrainMaterial->AddUniform<float>("u_Material.shininess", 1.0f);

		terrainMaterial->SetTexture(*tile);
		std::shared_ptr<Mesh> terrain = std::make_shared<Mesh>(vertices, tiles * tiles, indices, (tiles - 1) * (tiles - 1) * 6, *terrainMaterial);
		terrainModel = new Model(terrain);
		terrainModel->GetTransform().translate += glm::vec3(0.36f * 9, 0, -0.36f * 7);

		lampShader = new Shader("res/shaders/" SHADER("Lamp"));
		lampMaterial = new Material(*lampShader);
		cube = std::make_shared<Mesh>("res/smallercube.obj", *lampMaterial);
		lampModel = new Model(cube);
		lampModel->GetTransform().translate = light->position;

		snakeParts.reserve(50);

		for (unsigned int i = 0; i < 5; i++) {
			snakeParts.emplace_back(snakeCube);
			snakeParts[i].GetTransform().translate.x = TILE_SIZE * (i + 1);
		}

		dir = glm::vec3(-1, 0, 0);
	}


	void Snake3D::setDir(const glm::vec3& other)
	{
		dir = other;
	}

	void SnakeUpdate()
	{
		if (ticks--)
			return;

		for (unsigned int i = snakeParts.size() - 1; i > 0; i--)
			snakeParts[i].GetTransform().translate = snakeParts[i - 1].GetTransform().translate;

		snakeParts.front().GetTransform().translate += TILE_SIZE * dir;
		ticks = 15;
	}

	void Update()
	{
		if (Input::IsKeyPressed(SGL_KEY_RIGHT))
			setDir(glm::vec3(-1, 0, 0));

		else if (Input::IsKeyPressed(SGL_KEY_LEFT))
			setDir(glm::vec3(1, 0, 0));

		else if (Input::IsKeyPressed(SGL_KEY_UP))
			setDir(glm::vec3(0, 0, 1));

		else if (Input::IsKeyPressed(SGL_KEY_DOWN))
			setDir(glm::vec3(0, 0, -1));

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

		SnakeUpdate();

		for (Model &m : snakeParts) {
			renderer->Submit(m);
		}

		lampShader->SetUniformMat4f("u_Proj", camera->GetView() * lampModel->GetModelMatrix());

		renderer->SubmitLight(*light);
		renderer->Submit(*terrainModel);
		renderer->Submit(*lampModel);
		renderer->Render();
		renderer->Clear();
	}
};