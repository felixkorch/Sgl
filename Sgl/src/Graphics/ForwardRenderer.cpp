#include "Sgl/Graphics/ForwardRenderer.h"

namespace sgl
{
	ForwardRenderer::ForwardRenderer()
	{
		modelQueue.reserve(100);
		vertexUniformBuffer = new VertexUniforms;
		fragmentUniformBuffer = new FragmentUniforms;
	}

	ForwardRenderer::~ForwardRenderer()
	{
		delete vertexUniformBuffer;
		delete fragmentUniformBuffer;
	}

	void ForwardRenderer::Begin(const Camera& camera)
	{
		vertexUniformBuffer->view = camera.GetView();
	}

	void ForwardRenderer::Submit(const Model& model)
	{
		modelQueue.push_back(model);
	}

	void ForwardRenderer::SubmitLight(const Light& light)
	{
		fragmentUniformBuffer->light = light; // Only 1 light supported
	}


	void ForwardRenderer::Render()
	{
		for (Model& m : modelQueue) {
			vertexUniformBuffer->model = m.GetModelMatrix();
			const std::shared_ptr<Mesh>& mesh = m.GetMesh();
			SetUniforms(mesh->GetMaterial().GetShader());
			mesh->GetMaterial().BindUniforms();
			mesh->Draw();
		}
	}

	void ForwardRenderer::Clear()
	{
		modelQueue.clear();
	}

	void ForwardRenderer::SetUniforms(Shader& shader)
	{
		shader.SetSystemUniforms(vertexUniformBuffer, fragmentUniformBuffer);
	}
}