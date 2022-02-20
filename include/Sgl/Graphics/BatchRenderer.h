#pragma once
#include "Sgl/VertexArray.h"
#include "Sgl/VertexBuffer.h"
#include "Sgl/IndexBuffer.h"
#include "Sgl/Shader.h"
#include "Sgl/Graphics/Camera2D.h"
#include "Sgl/Graphics/Texture2D.h"
#include "Sgl/Graphics/Sprite.h"

namespace sgl {

	struct VertexData {
		glm::vec3 vertex;
		glm::vec4 color;
		glm::vec2 uv;
		float tid;
	};

	class BatchRenderer {
		static constexpr std::size_t MAX_SPRITES = 1000;
		static constexpr std::size_t VERTEX_SIZE = sizeof(VertexData);
		static constexpr std::size_t SPRITE_SIZE = (4 * VERTEX_SIZE);
		static constexpr std::size_t BUFFER_SIZE = SPRITE_SIZE * MAX_SPRITES;
		static constexpr std::size_t INDICES_COUNT = (6 * MAX_SPRITES);
		static constexpr std::size_t MAX_TEXTURES = 32;
	private:
		int width, height;
		unsigned int indexCount;
		VertexArray vao;
		std::unique_ptr<IndexBuffer> ibo;
		std::vector<Texture2D*> textures;
		std::unique_ptr<Shader> shader;
		VertexData* dataBuffer;
		Camera2D camera;
	private:
		float SubmitTexture(Texture2D* texture);
	public:
		BatchRenderer(int width, int height);
		void Begin();
		void Submit(const Sprite& sprite, glm::vec2 position);
		void End();
	};

}