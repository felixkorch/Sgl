#include "Sgl/Platform/Core/Renderer2D_Core.h"
#include "Sgl/OpenGL.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/Graphics/Camera2D.h"
#include "Sgl/Common.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>
#include <sstream>

namespace sgl
{
	Renderer2D_Core::Renderer2D_Core(int width, int height, const Shader& shader)
		: Renderer2D(width, height, shader)
	{
		Init();
	}

	Renderer2D_Core::~Renderer2D_Core()
	{
	}

	void Renderer2D_Core::Begin()
	{
		shader.Bind();
		vertexBuffer.Bind();
		vertexDataBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		shader.SetUniformMat4f("u_Proj", camera.GetViewMatrix());
	}

	void Renderer2D_Core::Submit(Renderable2D& renderable)
	{
		auto vertices = renderable.GetVertices();

		*vertexDataBuffer = { vertices[0], renderable.color, renderable.uv[0], renderable.tid };
		vertexDataBuffer++;
		*vertexDataBuffer = { vertices[1], renderable.color, renderable.uv[1], renderable.tid };
		vertexDataBuffer++;
		*vertexDataBuffer = { vertices[2], renderable.color, renderable.uv[2], renderable.tid };
		vertexDataBuffer++;
		*vertexDataBuffer = { vertices[3], renderable.color, renderable.uv[3], renderable.tid };
		vertexDataBuffer++;

		indexCount += 6;
	}

	void Renderer2D_Core::DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color)
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

	void Renderer2D_Core::DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color)
	{
		const auto v1 = glm::vec3(pos, 1);
		const auto v2 = glm::vec3(pos.x + size.x, pos.y, 1);
		const auto v3 = glm::vec3(pos.x + size.x, pos.y + size.y, 1);
		const auto v4 = glm::vec3(pos.x, pos.y + size.y, 1);
		DrawQuad(v1, v2, v3, v4, color);
	}

	void Renderer2D_Core::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	void Renderer2D_Core::Flush()
	{
        for (unsigned int i = 0; i < textures.size(); i++)
			textures[i]->Bind(i);

		vertexArray.Bind();
		indexBuffer.Bind();

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

		indexBuffer.Unbind();
		vertexBuffer.Unbind();
		vertexArray.Unbind();

		for (int i = 0; i < textures.size(); i++)
			textures[i]->Unbind();

		textures.clear();

		indexCount = 0;
	}

	void Renderer2D_Core::SubmitTexture(const Texture2D* texture)
	{
		if (textures.size() == MaxTextures) {
			SglCoreWarn("Max Textures exceeded");
			return;
		}
		textures.push_back(texture);
	}

	void Renderer2D_Core::Init()
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
		indexBuffer.Load(indices, IndicesCount);
		vertexArray.Unbind();

		shader.Bind();
		shader.SetUniformMat4f("u_Proj", camera.GetViewMatrix());

		static const int index[MaxTextures] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		shader.SetUniform1iv("f_Sampler", MaxTextures, index);

	}

	Renderer2D* Renderer2D::Create(int width, int height, const Shader& shader = Shader(Shader::Shader2D_Core))
	{
		return new Renderer2D_Core(width, height, shader);
	}

	Renderer2D* Renderer2D::Create(int width, int height)
	{
		return new Renderer2D_Core(width, height, Shader(Shader::Shader2D_Core));
	}
}
