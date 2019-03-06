#pragma once
#include "Sgl/VertexArray.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/IndexBuffer.h"
#include "Sgl/Renderable2D.h"
#include "Sgl/Shader.h"
#include "Sgl/Camera2D.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>

namespace sgl
{
	class BatchRenderer {
	private:
		static constexpr std::size_t MaxSprites = 5000;
		static constexpr std::size_t VertexSize = sizeof(VertexData);
		static constexpr std::size_t SpriteSize = (4 * VertexSize);
		static constexpr std::size_t BufferSize = SpriteSize * MaxSprites;
		static constexpr std::size_t IndicesCount = (6 * MaxSprites);

		VertexArray vertexArray;
		VertexBuffer vertexBuffer;
		IndexBuffer* indexBuffer;
		VertexBufferLayout layout;
		std::vector<VertexData> vertexDataBuffer;
		Shader shader;
		glm::vec2 screenSize;
		Camera2D camera;
		unsigned int indexCount;

	public:

		BatchRenderer(unsigned int width, unsigned int height, const Shader& shader)
			: indexCount(0), screenSize(width, height), shader(shader),
			camera(glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f))
		{
			Init();
		}

		~BatchRenderer()
		{
			delete indexBuffer;
		}

		void Begin()
		{
			shader.Bind();
			vertexBuffer.Bind();
			//vertexBuffer.BindAttrib(layout); // Instead of Vertex Arrays.
			/*
				This function isn't supported in GLES2 but should be used otherwise

				vertexDataBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			*/
			vertexDataBuffer.clear();
		}

		void Submit(Renderable2D& renderable)
		{
			for (const VertexData& i : renderable)
				vertexDataBuffer.emplace_back(i);
			indexCount += 6;
		}

		void DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color)
		{

			vertexDataBuffer.emplace_back(VertexData{ p0, color });
			vertexDataBuffer.emplace_back(VertexData{ p1, color });
			vertexDataBuffer.emplace_back(VertexData{ p2, color });
			vertexDataBuffer.emplace_back(VertexData{ p3, color });

			indexCount += 6;
		}

		void DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color = glm::vec4(1, 1, 1, 1))
		{
			const glm::vec3 v1 = glm::vec3(pos, 1);
			const glm::vec3 v2 = glm::vec3(pos.x + size.x, pos.y, 1);
			const glm::vec3 v3 = glm::vec3(pos.x + size.x, pos.y + size.y, 1);
			const glm::vec3 v4 = glm::vec3(pos.x, pos.y + size.y, 1);
			DrawQuad(v1, v2, v3, v4, color);
		}

		void End()
		{
			/*
				Used after call to glMapBuffer.

				glUnmapBuffer(GL_ARRAY_BUFFER);
			*/
			glBufferSubData(GL_ARRAY_BUFFER, 0, BufferSize, (void*)(vertexDataBuffer.data()));
			vertexBuffer.Unbind();
		}

		void Flush()
		{
			vertexArray.Bind();
			indexBuffer->Bind();

			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);

			indexBuffer->Unbind();
			vertexArray.Unbind();
			indexCount = 0;
		}

		void MoveCamera(const glm::vec2& val)
		{
			camera.Move(glm::vec3(val, 0));
			shader.SetUniformMat4f("u_Proj", camera.GetViewMatrix());
		}
	private:

		void Init()
		{
			vertexDataBuffer.reserve(BufferSize);
			vertexBuffer.Init_DynamicDraw(BufferSize);  // allocate memory in gpu
			layout.Push<float>(3); // position
			layout.Push<float>(4); // color
			vertexArray.AddBuffer(vertexBuffer, layout);
			//vertexBuffer.BindAttrib(layout); // Instead of Vertex Arrays.
			vertexBuffer.Unbind();

			unsigned int indices[IndicesCount];

			int offset = 0;
			for (int i = 0; i < IndicesCount; i += 6) {
				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;
				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}
			indexBuffer = new IndexBuffer(indices, IndicesCount);
			vertexArray.Unbind();

			shader.Bind();
			shader.SetUniformMat4f("u_Proj", camera.GetViewMatrix());

		}
	};
}