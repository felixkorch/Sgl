#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Sgl/Log.h"

namespace sgl
{
	class Camera2D {
	private:
		glm::mat4 ortho;
		glm::vec3 pos;
	public:
		constexpr Camera2D(const glm::mat4& ortho)
			: ortho(ortho), pos{} {}

		Camera2D(const glm::vec2& size)
			: ortho(glm::ortho(0.0f, size.x, 0.0f, size.y, -1.0f, 1.0f)), pos{}
		{
			SglCoreTrace("Created a new Camera2D with size ({}, {})", size.x, size.y);
		}

		Camera2D(int width, int height)
			: Camera2D(glm::vec2(width, height)) {}

		const glm::mat4 GetViewMatrix() const { return ortho * glm::translate(glm::mat4(1.0f), pos); }
		glm::vec3& GetPos() { return pos; }
	};
}
