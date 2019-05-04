#pragma once
#include "Sgl/VertexArray.h"
#include "Sgl/VertexBuffer.h"
#include "Sgl/IndexBuffer.h"
#include "Sgl/Shader.h"
#include "Sgl/Graphics/Camera2D.h"
#include "Sgl/Graphics/Renderable2D.h"
#include "Sgl/Graphics/Texture2D.h"
#include "Sgl/Graphics/Framebuffer2D.h"

#include <array>

namespace sgl {

	enum class RenderTarget {
		BUFFER = 0, SCREEN = 1
	};

	struct ScreenQuad {
		std::unique_ptr<IndexBuffer> ibo;
		std::unique_ptr<VertexArray> vao;
	};

	class Renderer2D {
	protected:
		static constexpr std::size_t MAX_SPRITES = 10000;
		static constexpr std::size_t VERTEX_SIZE = sizeof(VertexData);
		static constexpr std::size_t SPRITE_SIZE = (4 * VERTEX_SIZE);
		static constexpr std::size_t BUFFER_SIZE = SPRITE_SIZE * MAX_SPRITES;
		static constexpr std::size_t INDICES_COUNT = (6 * MAX_SPRITES);
		static constexpr std::size_t MAX_TEXTURES = 32;

		VertexArray vertexArray;
		std::unique_ptr<IndexBuffer> indexBuffer;
		std::unique_ptr<Shader> shader;
		Camera2D camera;
		std::vector<Texture2D*> textures;
		VertexData* dataBuffer;
		std::vector<glm::mat4> transformationStack;
		glm::mat4* transformationBack;
		FrameBuffer2D frameBuffer;
		RenderTarget renderTarget;
		int screenWidth, screenHeight;
		unsigned int indexCount;

		// Post-FX implementation not complete, just one pass atm.
		ScreenQuad screnQuad;
		std::unique_ptr<Shader> fxShader;

	public:
		Renderer2D(int width, int height);

		void Push(const glm::mat4& matrix, bool override);
		void Pop();
		void Begin();
		void Submit(Renderable2D* renderable);
		void DrawQuad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec4& color);
		void DrawRectangle(const glm::vec2& size, const glm::vec2& pos, const glm::vec4& color = glm::vec4(1, 1, 1, 1));
		void End();
		void Flush();
		void SetCamera(const Camera2D& _camera);
		void SetPostEffectsShader(Shader* shader);

	private:
		float SubmitTexture(Texture2D* texture);
		void Setup();

		static ScreenQuad CreateScreenQuad(int width, int height);
	};
}