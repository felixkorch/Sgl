#include "Sgl/OpenGL.h"
#include "Sgl/Graphics/Renderer2D.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/Graphics/Camera2D.h"
#include "Sgl/Log.h"
#include "Sgl/Application.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>

namespace sgl
{

	///
	/// TODO: Complete implementation
	///
	///

	Renderer2D::Renderer2D(int width, int height)
		: vertexArray()
		, indexBuffer()
		, shader()
		, camera(glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f))
		, textures()
		, dataBuffer(nullptr)
		, transformationStack()
		, transformationBack(nullptr)
		, frameBuffer(width, height)
		, renderTarget(RenderTarget::SCREEN)
		, screenWidth(width)
		, screenHeight(height)
		, indexCount(0)
		, screnQuad(CreateScreenQuad(width, height))
		, fxShader()
	{
		textures.reserve(MAX_TEXTURES);
		Setup();
	}

	void Renderer2D::Push(const glm::mat4& matrix, bool override)
	{
		if (override)
			transformationStack.push_back(matrix);
		else
			transformationStack.push_back(transformationStack.back() * matrix);

		transformationBack = &transformationStack.back();

	}

	void Renderer2D::Pop()
	{
		if (transformationStack.size() > 1)
			transformationStack.pop_back();

		transformationBack = &transformationStack.back();
	}

	void Renderer2D::SetCamera(const Camera2D& _camera)
	{
		camera = _camera;
	}

	// Testing post-effects (NOT final implementation)
	void Renderer2D::SetPostEffectsShader(Shader* shader)
	{
		if (shader == nullptr) {
			renderTarget = RenderTarget::SCREEN;
			return;
		}
		renderTarget = RenderTarget::BUFFER;
		fxShader = std::unique_ptr<Shader>(shader);
	}

	void Renderer2D::Submit(Renderable2D* renderable)
	{
		const auto minBounds = renderable->GetMinBounds();
		const auto maxBounds = renderable->GetMaxBounds();
		const auto& uvs = renderable->GetUVs();
		Texture2D* texture = renderable->GetTexture();

		float textureSlot = 0;
		if (texture)
			textureSlot = SubmitTexture(texture);

		*dataBuffer++ = { *transformationBack * minBounds, renderable->GetColor(), uvs[0], textureSlot };
		*dataBuffer++ = { *transformationBack * glm::vec4(maxBounds.x, minBounds.y, 1, 1), renderable->GetColor(), uvs[1], textureSlot };
		*dataBuffer++ = { *transformationBack * maxBounds, renderable->GetColor(), uvs[2], textureSlot };
		*dataBuffer++ = { *transformationBack * glm::vec4(minBounds.x, maxBounds.y, 1, 1), renderable->GetColor(), uvs[3], textureSlot };

		indexCount += 6;
	}

	void Renderer2D::DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color)
	{
		const auto uvs = Renderable2D::GetStandardUVs();
		for (int i = 0; i < 4; i++) {
			*dataBuffer = { p0, color, uvs[i], 0 };
			++dataBuffer;
		}
		indexCount += 6;
	}

	void Renderer2D::DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color)
	{
		const glm::vec3 v1 = glm::vec3(pos, 1);
		const glm::vec3 v2 = glm::vec3(pos.x + size.x, pos.y, 1);
		const glm::vec3 v3 = glm::vec3(pos.x + size.x, pos.y + size.y, 1);
		const glm::vec3 v4 = glm::vec3(pos.x, pos.y + size.y, 1);
		DrawQuad(v1, v2, v3, v4, color);
	}

	void Renderer2D::Begin()
	{
		if (renderTarget == RenderTarget::BUFFER) {
			frameBuffer.Bind();
			frameBuffer.Clear();
		}
		vertexArray.Bind();
		dataBuffer = (VertexData*)vertexArray.GetBuffer().GetInternalPointer();

	}

	void Renderer2D::End()
	{
		vertexArray.GetBuffer().ReleasePointer();
	}

	void Renderer2D::Flush()
	{
		shader->Bind();
		shader->SetUniformMat4f("u_Projection", camera.GetViewMatrix());
		for (int i = 0; i < textures.size(); i++)
			textures[i]->Bind(i);

		vertexArray.Bind();
		indexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		indexBuffer->Unbind();
		vertexArray.Unbind();

		for (int i = 0; i < textures.size(); i++)
			textures[i]->Unbind();

		textures.clear();
		indexCount = 0;

		if (renderTarget == RenderTarget::BUFFER) {
			frameBuffer.Unbind();
			fxShader->Bind();
			fxShader->SetUniformMat4f("u_Projection", camera.GetViewMatrix());
			frameBuffer.GetTexture()->Bind(0);

			screnQuad.vao->Bind();
			screnQuad.ibo->Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			screnQuad.ibo->Unbind();
			screnQuad.vao->Unbind();
		}
	}

	float Renderer2D::SubmitTexture(Texture2D* texture)
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

	void Renderer2D::Setup()
	{
		VertexBuffer* vbo = VertexBuffer::Create<BufferUsage::DYNAMIC>(BUFFER_SIZE);

		VertexBufferLayout layout;
		layout.Push<float>(3); // Position
		layout.Push<float>(4); // Color
		layout.Push<float>(2); // UV-Coords (Texture coordinates)
		layout.Push<float>(1); // TID (Texture ID)

		vertexArray.AddBuffer(vbo, layout);

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
		indexBuffer = std::unique_ptr<IndexBuffer>(new IndexBuffer(indices.data(), INDICES_COUNT));

		transformationStack.push_back(glm::mat4(1)); // Push identity matrix as default
		transformationBack = &transformationStack.back();

		shader = std::unique_ptr<Shader>(Shader::CreateFromString(Shader::Renderer2D));

	}

	ScreenQuad Renderer2D::CreateScreenQuad(int width, int height)
	{
		struct QuadVertex
		{
			glm::vec3 position;
			glm::vec2 uv;
		};

		QuadVertex vertices[4];

		vertices[0].position = glm::vec3(0, 0, 1);
		vertices[0].uv = glm::vec2(0, 0);
		vertices[1].position = glm::vec3(width, 0, 1);
		vertices[1].uv = glm::vec2(1, 0);
		vertices[2].position = glm::vec3(width, height, 1);
		vertices[2].uv = glm::vec2(1, 1);
		vertices[3].position = glm::vec3(0, height, 1);
		vertices[3].uv = glm::vec2(0, 1);

		unsigned int indices[6];

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;

		VertexArray* vao = VertexArray::Create();
		VertexBuffer* vbo = VertexBuffer::Create<BufferUsage::STATIC>(vertices, 4 * sizeof(QuadVertex));
		VertexBufferLayout layout;
		layout.Push<float>(3); // Position
		layout.Push<float>(2); // UV

		vao->AddBuffer(vbo, layout);

		IndexBuffer* ibo = IndexBuffer::Create(indices, 6);

		return { std::unique_ptr<IndexBuffer>(ibo), std::unique_ptr<VertexArray>(vao) };
	}

}