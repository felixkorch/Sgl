#include "Sgl/OpenGL.h"
#include "Sgl/Graphics/BatchRenderer.h"
#include "Sgl/Common.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/Graphics/Camera2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>

namespace sgl
{
	BatchRenderer::BatchRenderer(unsigned int width, unsigned int height, const Shader& shader)
		: indexCount(0), screenSize(width, height), shader(shader),
		camera(glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f))
	{
		Init();
	}

	BatchRenderer::~BatchRenderer()
	{
		delete indexBuffer;
	}

	void BatchRenderer::Begin()
	{
		shader.Bind();
		vertexBuffer.Bind();
		vertexDataBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer::Submit(Renderable2D& renderable)
	{
		const glm::vec3 boundsMin = glm::vec3(renderable.bounds.MinBounds(), 1);
		const glm::vec3 boundsMax = glm::vec3(renderable.bounds.MaxBounds(), 1);
		const glm::vec2& size = renderable.bounds.size;

		*vertexDataBuffer = { boundsMin, renderable.color };
		vertexDataBuffer++;
		*vertexDataBuffer = { glm::vec3(boundsMin.x + size.x, boundsMin.y, 1), renderable.color };
		vertexDataBuffer++;
		*vertexDataBuffer = { boundsMax, renderable.color };
		vertexDataBuffer++;
		*vertexDataBuffer = { glm::vec3(boundsMin.x, boundsMin.y + size.y, 1), renderable.color };
		vertexDataBuffer++;

		indexCount += 6;
	}

	void BatchRenderer::DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color)
	{
		*vertexDataBuffer = { p0, color };
		vertexDataBuffer++;
		*vertexDataBuffer = { p1, color };
		vertexDataBuffer++;
		*vertexDataBuffer = { p2, color };
		vertexDataBuffer++;
		*vertexDataBuffer = { p3, color };
		vertexDataBuffer++;

		indexCount += 6;
	}

	void BatchRenderer::DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color)
	{
		const glm::vec3 v1 = glm::vec3(pos, 1);
		const glm::vec3 v2 = glm::vec3(pos.x + size.x, pos.y, 1);
		const glm::vec3 v3 = glm::vec3(pos.x + size.x, pos.y + size.y, 1);
		const glm::vec3 v4 = glm::vec3(pos.x, pos.y + size.y, 1);
		DrawQuad(v1, v2, v3, v4, color);
	}

	void BatchRenderer::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	void BatchRenderer::Flush()
	{
		vertexArray.Bind();
		indexBuffer->Bind();

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

		indexBuffer->Unbind();
		vertexBuffer.Unbind();
		vertexArray.Unbind();

		indexCount = 0;
	}

	void BatchRenderer::MoveCamera(const glm::vec2& val)
	{
		camera.Move(glm::vec3(val, 0));
		shader.SetUniformMat4f("u_Proj", camera.GetViewMatrix());
	}

	void BatchRenderer::Init()
	{
		vertexBuffer.InitDynamicDraw(BufferSize);  // Allocate memory in GPU
		layout.Push<float>(3); // Position
		layout.Push<float>(4); // Color
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
		indexBuffer = new IndexBuffer(indices, IndicesCount);
		vertexArray.Unbind();

		shader.Bind();
		shader.SetUniformMat4f("u_Proj", camera.GetViewMatrix());

	}
}