#pragma once
#include "Sgl/Shader.h"
#include "Sgl/Model.h"
#include "Sgl/Camera.h"

namespace sgl
{
	class ForwardRenderer {
	private:
		VertexUniforms* m_VertexUniformBuffer;
		FragmentUniforms* m_FragmentUniformBuffer;
		std::vector<Model> m_ModelQueue;

	public:

		ForwardRenderer()
		{
			m_ModelQueue.reserve(100);
			m_VertexUniformBuffer = new VertexUniforms;
			m_FragmentUniformBuffer = new FragmentUniforms;
		}

		~ForwardRenderer()
		{
			delete m_VertexUniformBuffer;
			delete m_FragmentUniformBuffer;
		}

		void Begin(const Camera& camera)
		{
			m_VertexUniformBuffer->view = camera.getView();
		}

		void Submit(const Model& model)
		{
			m_ModelQueue.push_back(model);
		}

		void SubmitLight(const Light& lightProps, const glm::vec3& pos)
		{
			m_FragmentUniformBuffer->lightProps = lightProps;
			m_FragmentUniformBuffer->lightPos   = pos;
		}


		void Render()
		{
			for (Model& m : m_ModelQueue) {
				m_VertexUniformBuffer->model = m.getModelMatrix();
				const auto& mesh = m.getMesh();
				SetUniforms(mesh->getMaterial().GetShader());
				mesh->getMaterial().BindUniforms();
				mesh->draw();
			}
		}

		void Clear()
		{
			m_ModelQueue.clear();
		}

		void SetUniforms(Shader& shader)
		{
			shader.SetSystemUniforms(m_VertexUniformBuffer, m_FragmentUniformBuffer);
		}
	};
}