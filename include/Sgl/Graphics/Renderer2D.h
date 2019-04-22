#pragma once
#include "Sgl/VertexArray.h"
#include "Sgl/VertexBuffer.h"
#include "Sgl/IndexBuffer.h"
#include "Sgl/Shader.h"
#include "Sgl/Graphics/Camera2D.h"
#include "Sgl/Graphics/Renderable2D.h"
#include "Sgl/Graphics/Texture2D.h"

#include <array>

namespace sgl
{
	class Renderer2D {
	protected:
		static constexpr std::size_t MAX_SPRITES = 1000;
		static constexpr std::size_t VERTEX_SIZE = sizeof(VertexData);
		static constexpr std::size_t SPRITE_SIZE = (4 * VERTEX_SIZE);
		static constexpr std::size_t BUFFER_SIZE = SPRITE_SIZE * MAX_SPRITES;
		static constexpr std::size_t INDICES_COUNT = (6 * MAX_SPRITES);
		static constexpr std::size_t MAX_TEXTURES = 32 - 1;

		VertexBufferLayout layout;
        VertexArray vertexArray;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
        Shader shader;
		std::unique_ptr<Camera2D> camera;
		std::vector<Texture2D*> textures;
        std::vector<VertexData> vertexDataBuffer;
        std::vector<glm::mat4> transformationStack;
        glm::mat4* transformationBack;
        int screenWidth, screenHeight;

	public:
        Renderer2D(int width, int height, Shader&& shader);

        void Push(const glm::mat4& matrix, bool override);
        void Pop();
        void Begin();
        void Submit(Renderable2D* renderable);
        void DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color);
        void DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color = glm::vec4(1, 1, 1, 1));
        void End();
        void Flush();
        void SetCamera(std::unique_ptr<Camera2D>&& _camera);
        void SetShader(Shader&& _shader);
		static Renderer2D* Create(int width, int height);

    private:
        float SubmitTexture(Texture2D* texture);
        void Setup();
	};
}
