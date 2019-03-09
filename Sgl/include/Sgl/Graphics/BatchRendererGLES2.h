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

	class BatchRendererGLES2 {
	private:
		static constexpr std::size_t MaxSprites = 100;
		static constexpr std::size_t VertexSize = sizeof(VertexData);
		static constexpr std::size_t SpriteSize = (4 * VertexSize);
		static constexpr std::size_t BufferSize = SpriteSize * MaxSprites;
		static constexpr std::size_t IndicesCount = (6 * MaxSprites);

		VertexBuffer vertexBuffer;
		IndexBuffer* indexBuffer;
		VertexBufferLayout layout;
		std::vector<VertexData> vertexDataBuffer;
		Shader shader;
		glm::vec2 screenSize;
		Camera2D camera;
		unsigned int indexCount;

	public:
		BatchRendererGLES2(unsigned int width, unsigned int height, const Shader& shader);
		~BatchRendererGLES2();

		void Begin();
		void Submit(Renderable2D& renderable);
		void DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color);
		void DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color = glm::vec4(1, 1, 1, 1));
		void End();
		void Flush();
		void MoveCamera(const glm::vec2& val);
	private:
		void Init();
	};
}