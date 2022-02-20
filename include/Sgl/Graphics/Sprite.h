#pragma once

#include <memory>

#include "Sgl/Graphics/Texture2D.h"
#include "glm/glm.hpp"

// Useful for debugging
#define SGL_COLOR_GREEN glm::vec4(0, 1, 0, 1)
#define SGL_COLOR_BLUE glm::vec4(0, 1, 1, 1)
#define SGL_COLOR_RED glm::vec4(1, 0, 0, 1)

namespace sgl {

	class Sprite {
	public:
		std::shared_ptr<Texture2D> texture;
		glm::vec4 color;
		glm::vec2 size; // 0 means the full width/height
		glm::vec2 uv = {0, 0}; // texture coords
		int nCols = 0; // 0 is same as 1

		void FromTexture(std::shared_ptr<Texture2D> texture, int width = 0, int height = 0);
		void FromColor(glm::vec4 color, int width, int height);
	};

}