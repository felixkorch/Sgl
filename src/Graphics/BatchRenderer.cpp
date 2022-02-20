#include "Sgl/Graphics/BatchRenderer.h"
#include "Sgl/OpenGL.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/Graphics/Camera2D.h"
#include "Sgl/Log.h"
#include "Sgl/Application.h"
#include "glm/glm.hpp"

namespace sgl {

	BatchRenderer::BatchRenderer(int width, int height) :
		width(width),
		height(height),
		indexCount(0),
		textures(),
		vao(),
		ibo(),
		shader(),
		dataBuffer(nullptr),
		camera(glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f))
	{
		textures.reserve(MAX_TEXTURES);

		VertexBuffer* vbo = VertexBuffer::Create<BufferUsage::DYNAMIC>(BUFFER_SIZE);

		VertexBufferLayout layout;
		layout.Push<float>(3); // Position
		layout.Push<float>(4); // Color
		layout.Push<float>(2); // UV-Coords (Texture coordinates)
		layout.Push<float>(1); // TID (Texture ID)

		vao.AddBuffer(vbo, layout);

		std::vector<unsigned int> indices(INDICES_COUNT);

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
		ibo = std::unique_ptr<IndexBuffer>(new IndexBuffer(indices.data(), INDICES_COUNT));

		shader = std::unique_ptr<Shader>(Shader::CreateFromString(Shader::Renderer2D));
	}

	float BatchRenderer::SubmitTexture(Texture2D* texture)
	{
		if (textures.size() == MAX_TEXTURES) {
			SGL_CORE_WARN("Max textures exceeded!");
			return textures.size();
		}
		if (texture->GetHandle() == 0) {
			SGL_CORE_WARN("Invalid texture submitted!");
			return textures.size();
		}
		textures.push_back(texture);
		return textures.size();
	}

	void BatchRenderer::Begin()
	{
		vao.Bind();
		dataBuffer = (VertexData*)vao.GetBuffer().GetInternalPointer();
	}

	void BatchRenderer::Submit(const Sprite& sprite, glm::vec2 position)
	{
		const int sprWidth = sprite.size.x;
		const int sprHeight = sprite.size.y;

		const int uv_x = sprite.uv.x;
		const int uv_y = sprite.uv.y;

		glm::vec3 coords[] = {
			glm::vec3(position, 1),
			glm::vec3(position.x + sprWidth, position.y, 1),
			glm::vec3(position.x + sprWidth, position.y + sprHeight, 1),
			glm::vec3(position.x, position.y + sprHeight, 1)
		};

		glm::vec2 uvs[4] = {glm::vec2(0, 0),
							glm::vec2(1, 0),
							glm::vec2(1, 1),
							glm::vec2(0, 1)};

		float textureSlot = 0;
		if (sprite.texture)
			textureSlot = SubmitTexture(sprite.texture.get());

		for (int i = 0; i < 4; i++) {
			//glm::vec2 uv(uvs[i].x / (float)sprite.texture->GetWidth(), uvs[i].y / (float)sprite.texture->GetHeight());
			//printf("UV X: %f Y: %f\n", uv.x, uv.y);
			*dataBuffer = { coords[i], sprite.color, uvs[i], 0};
			++dataBuffer;
		}
		indexCount += 6;
	}

	void BatchRenderer::End()
	{
		vao.GetBuffer().ReleasePointer();

		shader->Bind();
		shader->SetUniformMat4f("u_Projection", camera.GetViewMatrix());
		for (int i = 0; i < textures.size(); i++)
			textures[i]->Bind(i);

		vao.Bind();
		ibo->Bind();
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		ibo->Unbind();
		vao.Unbind();

		for (int i = 0; i < textures.size(); i++)
			textures[i]->Unbind();

		textures.clear();
		indexCount = 0;
	}

}