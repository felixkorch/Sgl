#pragma once
#include "Sgl/Graphics/Renderer2D.h"

namespace sgl
{
	class Renderer2D_Core : public Renderer2D {
	private:
		VertexArray vertexArray;
		VertexData* vertexDataBuffer;

	public:
		Renderer2D_Core(int width, int height, const Shader& shader);
		~Renderer2D_Core();
		Renderer2D_Core(const Renderer2D_Core&) = delete;
		void operator=(const Renderer2D_Core&) = delete;

		void Begin() override;
		void Submit(Renderable2D& renderable) override;
		void DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color) override;
		void DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color = glm::vec4(1, 1, 1, 1)) override;
		void End() override;
		void Flush() override;
		void SubmitTexture(const Texture2D* texture) override;

	private:
		void Init();
	};
}