#include "Sgl/OpenGL.h"
#include "Sgl/Graphics/Renderer2D.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/Graphics/Camera2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>

namespace sgl
{
    Renderer2D::Renderer2D(int width, int height, Shader&& shader)
        : shader(std::move(shader))
        , camera(new Camera2D(glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f)))
        , screenWidth(width)
        , screenHeight(height)
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

    void Renderer2D::SetCamera(std::unique_ptr<Camera2D>&& _camera)
    {
        camera = std::move(_camera);
    }

    void Renderer2D::SetShader(Shader&& _shader)
    {
        shader = std::move(_shader);
    }

	void Renderer2D::Submit(Renderable2D* renderable)
	{
		const auto minBounds = renderable->GetMinBounds();
		const auto maxBounds = renderable->GetMaxBounds();
		const auto& uvs      = renderable->GetUVs();
        Texture2D* texture   = renderable->GetTexture();

        float textureSlot = 0;
        if (texture)
            textureSlot = SubmitTexture(texture);

        vertexDataBuffer.emplace_back(VertexData{ minBounds, renderable->GetColor(), uvs[0], textureSlot });
        vertexDataBuffer.emplace_back(VertexData{ glm::vec3(maxBounds.x, minBounds.y, 1) , renderable->GetColor(), uvs[1], textureSlot });
        vertexDataBuffer.emplace_back(VertexData{ maxBounds, renderable->GetColor(), uvs[2], textureSlot });
        vertexDataBuffer.emplace_back(VertexData{ glm::vec3(minBounds.x, maxBounds.y, 1), renderable->GetColor(), uvs[3], textureSlot });
	}

	void Renderer2D::DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color)
	{
		const auto uvs = Renderable2D::GetStandardUVs();
        for(int i = 0; i < 4; i++)
            vertexDataBuffer.emplace_back(VertexData{ p0, color, uvs[i], 0 });
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
        shader.Bind();
        vertexDataBuffer.clear();
        shader.SetUniformMat4f("u_Projection", camera->GetViewMatrix());
    }

	void Renderer2D::End()
	{
		vertexBuffer.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, BUFFER_SIZE, (void*)(vertexDataBuffer.data()));
		vertexBuffer.Unbind();
	}

	void Renderer2D::Flush()
	{
        for (int i = 0; i < textures.size(); i++) {
            textures[i]->Bind(i);
            shader.SetUniform1i("u_Sampler[" + std::to_string(i) + "]", i);
        }

		vertexBuffer.Bind();
		indexBuffer.Bind();
		vertexBuffer.BindLayout(layout);
		glDrawElements(GL_TRIANGLES, vertexDataBuffer.size() * 4 * 6, GL_UNSIGNED_INT, nullptr);

		vertexBuffer.Unbind();
		indexBuffer.Unbind();

		for (int i = 0; i < textures.size(); i++)
			textures[i]->Unbind();

		textures.clear();
	}

	float Renderer2D::SubmitTexture(Texture2D* texture)
	{
		if (textures.size() == MAX_TEXTURES) {
			SGL_CORE_WARN("Max textures exceeded!");
			return textures.size();
		}
        if (texture->GetID() == 0) {
            SGL_CORE_WARN("Invalid texture submitted!");
            return textures.size();
        }
		textures.push_back(texture);
        return textures.size();
	}

	void Renderer2D::Setup()
	{
		vertexDataBuffer.reserve(BUFFER_SIZE);
		vertexBuffer.InitDynamicDraw(BUFFER_SIZE);  // Allocate memory in GPU
		layout.Push<float>(3); // Position
		layout.Push<float>(4); // Color
		layout.Push<float>(2); // UV-Coords (Texture coordinates)
		layout.Push<float>(1); // TID (Texture ID)

        vertexArray.Bind();
        vertexArray.AddBuffer(vertexBuffer, layout);
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

        transformationStack.push_back(glm::mat4(1));
        transformationBack = &transformationStack.back();
	}

	Renderer2D* Renderer2D::Create(int width, int height)
	{
        #ifndef PLATFORM_WEB
        const char* shaderProgram = Shader::Shader2D_Core;
        #else
        const char* shaderProgram = Shader::Shader2D_ES3;
        #endif

        Shader shader;
        shader.LoadFromString(shaderProgram);
        Renderer2D* renderer = new Renderer2D(width, height, std::move(shader));
        return renderer;
	}

}