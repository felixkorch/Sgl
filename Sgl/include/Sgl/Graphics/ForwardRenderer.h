#pragma once
#include "Sgl/Shader.h"
#include "Sgl/Graphics/Model.h"
#include "Sgl/Graphics/Camera.h"

namespace sgl
{
	class ForwardRenderer {
	private:
		VertexUniforms* vertexUniformBuffer;
		FragmentUniforms* fragmentUniformBuffer;
		std::vector<Model> modelQueue;

	public:
		ForwardRenderer();
		~ForwardRenderer();

		void Begin(const Camera& camera);
		void Submit(const Model& model);
		void SubmitLight(const Light& light);
		void Render();
		void Clear();
		void SetUniforms(Shader& shader);
	};
}