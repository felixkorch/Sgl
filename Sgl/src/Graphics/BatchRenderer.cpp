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
		//vertexBuffer.BindAttrib(layout); // Instead of Vertex Arrays.
		/*
			This function isn't supported in GLES2 but should be used otherwise
			vertexDataBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		*/
		vertexDataBuffer.clear();
	}

	void BatchRenderer::Submit(Renderable2D& renderable)
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

	void BatchRenderer::DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color)
	{

		vertexDataBuffer.emplace_back(VertexData{ p0, color });
		vertexDataBuffer.emplace_back(VertexData{ p1, color });
		vertexDataBuffer.emplace_back(VertexData{ p2, color });
		vertexDataBuffer.emplace_back(VertexData{ p3, color });

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
		/*
			Used after call to glMapBuffer.
			glUnmapBuffer(GL_ARRAY_BUFFER);
		*/
		glBufferSubData(GL_ARRAY_BUFFER, 0, BufferSize, (void*)(vertexDataBuffer.data()));
		vertexBuffer.Unbind();
	}

	void BatchRenderer::Flush()
	{
		vertexBuffer.Bind();
		vertexArray.Bind();
		indexBuffer->Bind();

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);

		indexBuffer->Unbind();
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
}