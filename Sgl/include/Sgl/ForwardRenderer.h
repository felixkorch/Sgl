#pragma once
#include "Sgl/Shader.h"
#include "Sgl/Model.h"
#include "Sgl/Camera.h"

namespace sgl
{
	class ForwardRenderer {
	private:
		VertexUniforms* vertexUniformBuffer;
		FragmentUniforms* fragmentUniformBuffer;
		std::vector<Model> modelQueue;

	public:

		ForwardRenderer()
		{
			modelQueue.reserve(100);
			vertexUniformBuffer = new VertexUniforms;
			fragmentUniformBuffer = new FragmentUniforms;
		}

		~ForwardRenderer()
		{
			delete vertexUniformBuffer;
			delete fragmentUniformBuffer;
		}

		void Begin(const Camera& camera)
		{
			vertexUniformBuffer->view = camera.getView();
		}

		void Submit(const Model& model)
		{
			modelQueue.push_back(model);
		}

		void SubmitLight(const Light& lightProps, const glm::vec3& pos)
		{
			fragmentUniformBuffer->lightProps = lightProps;
			fragmentUniformBuffer->lightPos   = pos;
		}


		void Render()
		{
			for (Model& m : modelQueue) {
				vertexUniformBuffer->model = m.getModelMatrix();
				const auto& mesh = m.getMesh();
				SetUniforms(mesh->getMaterial().GetShader());
				mesh->getMaterial().BindUniforms();
				mesh->draw();
			}
		}

		void Clear()
		{
			modelQueue.clear();
		}

		void SetUniforms(Shader& shader)
		{
			shader.SetSystemUniforms(vertexUniformBuffer, fragmentUniformBuffer);
		}
	};
}