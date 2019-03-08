#pragma once
#include "Sgl/Shader.h"
#include "Sgl/Graphics/Model.h"
#include "Sgl/Graphics/Camera.h"

namespace sgl
{

	/* Set of standard uniforms */
	struct VertexUniforms {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
	};

	struct FragmentUniforms {
		glm::vec3 cameraPos;
		Light light;
	};

	class ForwardRenderer {
	private:
		VertexUniforms* vertexUniforms; // Model / View / Projection
		FragmentUniforms* fragmentUniforms; // Light / Camera
		std::vector<Model> modelQueue;

	public:
		ForwardRenderer();
		~ForwardRenderer();

		void Begin(const Camera& camera);
		void Submit(const Model& model);
		void SubmitLight(const Light& light);
		void Render();
		void Clear();
		void SetStandardUniforms(Shader& shader);
	};
}