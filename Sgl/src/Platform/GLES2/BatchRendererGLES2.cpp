#include "Sgl/OpenGL.h"
#include "Sgl/Platform/GLES2/BatchRendererGLES2.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/Graphics/Camera2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>

namespace sgl
{
	BatchRendererGLES2::BatchRendererGLES2(unsigned int width, unsigned int height, const Shader& shader)
		: BatchRenderer(width, height, shader)
	{
		Init();
	}

	BatchRendererGLES2::~BatchRendererGLES2() {}

	void BatchRendererGLES2::Begin()
	{
		shader.Bind();
		vertexDataBuffer.clear();
	}

	void BatchRendererGLES2::Submit(Renderable2D& renderable)
	{
		const glm::vec3 boundsMin = glm::vec3(renderable.bounds.MinBounds(), 1);
		const glm::vec3 boundsMax = glm::vec3(renderable.bounds.MaxBounds(), 1);
		const glm::vec2& size = renderable.bounds.size;

		vertexDataBuffer.emplace_back(VertexData{ boundsMin, renderable.color });
		vertexDataBuffer.emplace_back(VertexData{ glm::vec3(boundsMin.x + size.x, boundsMin.y, 1), renderable.color });
		vertexDataBuffer.emplace_back(VertexData{ boundsMax, renderable.color });
		vertexDataBuffer.emplace_back(VertexData{ glm::vec3(boundsMin.x, boundsMin.y + size.y, 1), renderable.color });

		indexCount += 6;
	}

	void BatchRendererGLES2::DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color)
	{
		vertexDataBuffer.emplace_back(VertexData{ p0, color });
		vertexDataBuffer.emplace_back(VertexData{ p1, color });
		vertexDataBuffer.emplace_back(VertexData{ p2, color });
		vertexDataBuffer.emplace_back(VertexData{ p3, color });

		indexCount += 6;
	}

	void BatchRendererGLES2::DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color)
	{
		const glm::vec3 v1 = glm::vec3(pos, 1);
		const glm::vec3 v2 = glm::vec3(pos.x + size.x, pos.y, 1);
		const glm::vec3 v3 = glm::vec3(pos.x + size.x, pos.y + size.y, 1);
		const glm::vec3 v4 = glm::vec3(pos.x, pos.y + size.y, 1);
		DrawQuad(v1, v2, v3, v4, color);
	}

	void BatchRendererGLES2::End()
	{
		vertexBuffer.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, BufferSize, (void*)(vertexDataBuffer.data()));
		vertexBuffer.Unbind();
	}

	void BatchRendererGLES2::Flush()
	{
		vertexBuffer.Bind();
		indexBuffer.Bind();
		vertexBuffer.BindLayout(layout);

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

		vertexBuffer.Unbind();
		indexBuffer.Unbind();

		indexCount = 0;
	}

	void BatchRendererGLES2::MoveCamera(const glm::vec2& val)
	{
		camera.Move(glm::vec3(val, 0));
		shader.SetUniformMat4f("u_Proj", camera.GetViewMatrix());
	}

	void BatchRendererGLES2::Init()
	{
		vertexDataBuffer.reserve(BufferSize);
		vertexBuffer.InitDynamicDraw(BufferSize);  // Allocate memory in GPU
		layout.Push<float>(3); // Position
		layout.Push<float>(4); // Color

		vertexBuffer.BindLayout(layout); // Instead of Vertex Arrays.
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
		indexBuffer.Init(indices, IndicesCount);

		shader.Bind();
		shader.SetUniformMat4f("u_Proj", camera.GetViewMatrix());
	}

	BatchRenderer* BatchRenderer::MakeBatchRenderer(unsigned int width, unsigned int height, const Shader& shader)
	{
		return new BatchRendererGLES2(width, height, shader);
	}
}