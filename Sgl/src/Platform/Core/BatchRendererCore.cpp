#include "Sgl/Platform/Core/BatchRendererCore.h"
#include "Sgl/OpenGL.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/Graphics/Camera2D.h"
#include "Sgl/Common.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>

namespace sgl
{
	BatchRendererCore::BatchRendererCore(unsigned int width, unsigned int height, const Shader& shader)
		: BatchRenderer(width, height, shader)
	{
		Init();
	}

	BatchRendererCore::~BatchRendererCore()
	{
		delete vertexDataBuffer;
	}

	void BatchRendererCore::Begin()
	{
		shader.Bind();
		vertexBuffer.Bind();
		vertexDataBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRendererCore::Submit(Renderable2D& renderable)
	{
		const glm::vec3 boundsMin = glm::vec3(renderable.bounds.MinBounds(), 1);
		const glm::vec3 boundsMax = glm::vec3(renderable.bounds.MaxBounds(), 1);
		const glm::vec2& size = renderable.bounds.size;

		*vertexDataBuffer = { boundsMin, renderable.color, renderable.uvCoords[0], renderable.tid };
		vertexDataBuffer++;
		*vertexDataBuffer = { glm::vec3(boundsMin.x + size.x, boundsMin.y, 1), renderable.color, renderable.uvCoords[1], renderable.tid };
		vertexDataBuffer++;
		*vertexDataBuffer = { boundsMax, renderable.color, renderable.uvCoords[2], renderable.tid };
		vertexDataBuffer++;
		*vertexDataBuffer = { glm::vec3(boundsMin.x, boundsMin.y + size.y, 1), renderable.color, renderable.uvCoords[3], renderable.tid };
		vertexDataBuffer++;

		indexCount += 6;
	}

	void BatchRendererCore::DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color)
	{
		const auto uvs = Renderable2D::GetStandardUVs();

		*vertexDataBuffer = { p0, color, uvs[0], 0 };
		vertexDataBuffer++;
		*vertexDataBuffer = { p1, color, uvs[1], 0 };
		vertexDataBuffer++;
		*vertexDataBuffer = { p2, color, uvs[2], 0 };
		vertexDataBuffer++;
		*vertexDataBuffer = { p3, color, uvs[3], 0 };
		vertexDataBuffer++;

		indexCount += 6;
	}

	void BatchRendererCore::DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color)
	{
		const glm::vec3 v1 = glm::vec3(pos, 1);
		const glm::vec3 v2 = glm::vec3(pos.x + size.x, pos.y, 1);
		const glm::vec3 v3 = glm::vec3(pos.x + size.x, pos.y + size.y, 1);
		const glm::vec3 v4 = glm::vec3(pos.x, pos.y + size.y, 1);
		DrawQuad(v1, v2, v3, v4, color);
	}

	void BatchRendererCore::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	void BatchRendererCore::Flush()
	{
		vertexArray.Bind();
		indexBuffer.Bind();

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

		indexBuffer.Unbind();
		vertexBuffer.Unbind();
		vertexArray.Unbind();

		indexCount = 0;
	}

	void BatchRendererCore::MoveCamera(const glm::vec2& val)
	{
		camera.Move(glm::vec3(val, 0));
		shader.SetUniformMat4f("u_Proj", camera.GetViewMatrix());
	}

	void BatchRendererCore::Init()
	{
		vertexBuffer.InitDynamicDraw(BufferSize);  // Allocate memory in GPU
		layout.Push<float>(3); // Position
		layout.Push<float>(4); // Color
		layout.Push<float>(2); // UV-Coords (Texture coordinates)
		layout.Push<float>(1); // TID (Texture ID)
		vertexArray.AddBuffer(vertexBuffer, layout);
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
		vertexArray.Unbind();

		shader.Bind();
		shader.SetUniformMat4f("u_Proj", camera.GetViewMatrix());

	}

	BatchRenderer* BatchRenderer::MakeBatchRenderer(unsigned int width, unsigned int height, const Shader& shader)
	{
		return new BatchRendererCore(width, height, shader);
	}
}