#pragma once
#include "Sgl/Graphics/Renderer2D.h"

namespace sgl
{
	class Renderer2DCore : public Renderer2D {
	private:
		VertexArray vertexArray;
		VertexData* vertexDataBuffer;

	public:
		Renderer2DCore(unsigned int width, unsigned int height, const Shader& shader);
		~Renderer2DCore();
		Renderer2DCore(const Renderer2DCore&) = delete;
		void operator=(const Renderer2DCore&) = delete;

		void Begin() override;
		void Submit(Renderable2D& renderable) override;
		void DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color) override;
		void DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color = glm::vec4(1, 1, 1, 1)) override;
		void End() override;
		void Flush() override;
		void MoveCamera(const glm::vec2& val) override;
		void SubmitTexture(const Texture* texture) override;

	private:
		void Init();
	};
}