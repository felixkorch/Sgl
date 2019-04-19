#include "Sgl/OpenGL.h"
#include "Sgl/Platform/GLES2/Renderer2D_ES2.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/Graphics/Camera2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>

namespace sgl
{
	Renderer2D_ES2::Renderer2D_ES2(int width, int height, Shader&& shader)
		: Renderer2D(width, height, std::move(shader))
	{
        Setup();
    }

	Renderer2D_ES2::~Renderer2D_ES2() {}

	void Renderer2D_ES2::Begin()
	{
		shader.Bind();
		vertexDataBuffer.clear();
		shader.SetUniformMat4f("u_Projection", camera.GetViewMatrix());
	}

	void Renderer2D_ES2::Submit(Renderable2D& renderable)
	{
		auto vertices = renderable.GetVertices();

		vertexDataBuffer.emplace_back(VertexData{ vertices[0], renderable.color, renderable.uv[0], renderable.tid });
		vertexDataBuffer.emplace_back(VertexData{ vertices[1], renderable.color, renderable.uv[1], renderable.tid });
		vertexDataBuffer.emplace_back(VertexData{ vertices[2], renderable.color, renderable.uv[2], renderable.tid });
		vertexDataBuffer.emplace_back(VertexData{ vertices[3], renderable.color, renderable.uv[3], renderable.tid });

		indexCount += 6;
	}

	void Renderer2D_ES2::DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color)
	{
		const auto uvs = Renderable2D::GetStandardUVs();

		vertexDataBuffer.emplace_back(VertexData{ p0, color, uvs[0], 0 });
		vertexDataBuffer.emplace_back(VertexData{ p1, color, uvs[1], 0 });
		vertexDataBuffer.emplace_back(VertexData{ p2, color, uvs[2], 0 });
		vertexDataBuffer.emplace_back(VertexData{ p3, color, uvs[3], 0 });

		indexCount += 6;
	}

	void Renderer2D_ES2::DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color)
	{
		const glm::vec3 v1 = glm::vec3(pos, 1);
		const glm::vec3 v2 = glm::vec3(pos.x + size.x, pos.y, 1);
		const glm::vec3 v3 = glm::vec3(pos.x + size.x, pos.y + size.y, 1);
		const glm::vec3 v4 = glm::vec3(pos.x, pos.y + size.y, 1);
		DrawQuad(v1, v2, v3, v4, color);
	}

	void Renderer2D_ES2::End()
	{
		vertexBuffer.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, BUFFER_SIZE, (void*)(vertexDataBuffer.data()));
		vertexBuffer.Unbind();
	}

	void Renderer2D_ES2::Flush()
	{
        for (int i = 0; i < textures.size(); i++) {
            textures[i]->Bind(i);
            shader.SetUniform1i("u_Sampler[" + std::to_string(i) + "]", i);
        }

		vertexBuffer.Bind();
		indexBuffer.Bind();
		vertexBuffer.BindLayout(layout);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

		vertexBuffer.Unbind();
		indexBuffer.Unbind();

		for (int i = 0; i < textures.size(); i++)
			textures[i]->Unbind();

		textures.clear();

		indexCount = 0;
	}

	void Renderer2D_ES2::SubmitTexture(const Texture2D* texture)
	{
		if (textures.size() == MAX_TEXTURES) {
			SGL_CORE_WARN("Max Textures exceeded");
			return;
		}
		textures.push_back(texture);
	}

	void Renderer2D_ES2::Setup()
	{
		vertexDataBuffer.reserve(BUFFER_SIZE);
		vertexBuffer.InitDynamicDraw(BUFFER_SIZE);  // Allocate memory in GPU
		layout.Push<float>(3); // Position
		layout.Push<float>(4); // Color
		layout.Push<float>(2); // UV-Coords (Texture coordinates)
		layout.Push<float>(1); // TID (Texture ID)

		vertexBuffer.BindLayout(layout); // Instead of Vertex Arrays
		vertexBuffer.Unbind();

		unsigned int indices[INDICES_COUNT];

		int offset = 0;
		for (int i = 0; i < INDICES_COUNT; i += 6) {
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}
		indexBuffer.Load(indices, INDICES_COUNT);
	}

	Renderer2D* Renderer2D::Create(int width, int height)
	{
        Shader shader;
        shader.LoadFromString(Shader::Shader2D_ES2);
        Renderer2D* renderer = new Renderer2D_ES2(width, height, std::move(shader));
        return renderer;
	}

}