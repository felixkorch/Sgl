#include "Sgl/Graphics/ForwardRenderer.h"

namespace sgl
{
	ForwardRenderer::ForwardRenderer()
	{
		modelQueue.reserve(100);
		vertexUniforms = new VertexUniforms;
		fragmentUniforms = new FragmentUniforms;
	}

	ForwardRenderer::~ForwardRenderer()
	{
		delete vertexUniforms;
		delete fragmentUniforms;
	}

	void ForwardRenderer::Begin(const Camera& camera)
	{
		vertexUniforms->view = camera.GetView();
	}

	void ForwardRenderer::Submit(const Model& model)
	{
		modelQueue.push_back(model);
	}

	void ForwardRenderer::SubmitLight(const Light& light) // Only one light atm
	{
		fragmentUniforms->light = light;
	}

	void ForwardRenderer::Render()
	{
		for (Model& m : modelQueue) {
			vertexUniforms->model = m.GetModelMatrix();
			const std::shared_ptr<Mesh>& mesh = m.GetMesh();
			SetStandardUniforms(mesh->GetMaterial().GetShader());
			mesh->GetMaterial().BindUniforms();
			mesh->Draw();
		}
	}

	void ForwardRenderer::Clear()
	{
		modelQueue.clear();
	}

	void ForwardRenderer::SetStandardUniforms(Shader& shader)
	{
		shader.Bind();
		shader.SetUniformMat4f("u_Model", vertexUniforms->model);
		shader.SetUniformMat4f("u_Proj", vertexUniforms->view * vertexUniforms->model);
		shader.SetUniform3f("u_Light.ambient", fragmentUniforms->light.ambient);
		shader.SetUniform3f("u_Light.diffuse", fragmentUniforms->light.diffuse);
		shader.SetUniform3f("u_Light.specular", fragmentUniforms->light.specular);
		shader.SetUniform3f("u_Light.position", fragmentUniforms->light.position);
	}
}