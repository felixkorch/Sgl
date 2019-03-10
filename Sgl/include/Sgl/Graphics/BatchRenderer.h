#pragma once
#include "Sgl/VertexArray.h"
#include "Sgl/VertexBuffer.h"
#include "Sgl/IndexBuffer.h"
#include "Sgl/Shader.h"
#include "Sgl/Graphics/Camera2D.h"
#include "Sgl/Graphics/Renderable2D.h"

#include <array>

namespace sgl
{
	class BatchRenderer {
	protected:
		static constexpr std::size_t MaxSprites = 1000;
		static constexpr std::size_t VertexSize = sizeof(VertexData);
		static constexpr std::size_t SpriteSize = (4 * VertexSize);
		static constexpr std::size_t BufferSize = SpriteSize * MaxSprites;
		static constexpr std::size_t IndicesCount = (6 * MaxSprites);

		VertexBufferLayout layout;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
		Shader shader;
		glm::vec2 screenSize;
		Camera2D camera;
		unsigned int indexCount;

	public:
		BatchRenderer(unsigned int width, unsigned int height, const Shader& shader)
			: indexCount(0), screenSize(width, height), shader(shader),
			camera(glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f)) {}

		virtual ~BatchRenderer() {}

		virtual void Begin() = 0;
		virtual void Submit(Renderable2D& renderable) = 0;
		virtual void DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color) = 0;
		virtual void DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color = glm::vec4(1, 1, 1, 1)) = 0;
		virtual void End() = 0;
		virtual void Flush() = 0;
		virtual void MoveCamera(const glm::vec2& val) = 0;

		static BatchRenderer* MakeBatchRenderer(unsigned int width, unsigned int height, const Shader& shader);
	};
}