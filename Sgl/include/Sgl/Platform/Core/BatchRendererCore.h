#pragma once
#include "Sgl/Graphics/BatchRenderer.h"

namespace sgl
{
	class BatchRendererCore : public BatchRenderer {
	private:
		VertexArray vertexArray;
		VertexData* vertexDataBuffer;

	public:
		BatchRendererCore(unsigned int width, unsigned int height, const Shader& shader);
		~BatchRendererCore();
		BatchRendererCore(const BatchRendererCore&) = delete;
		void operator=(const BatchRendererCore&) = delete;

		void Begin() override;
		void Submit(Renderable2D& renderable) override;
		void DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color) override;
		void DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color = glm::vec4(1, 1, 1, 1)) override;
		void End() override;
		void Flush() override;
		void MoveCamera(const glm::vec2& val) override;

	private:
		void Init();
	};
}