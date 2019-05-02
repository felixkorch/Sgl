#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace sgl
{
	class Camera2D {
		glm::mat4 ortho;
		glm::vec3 pos;
	public:
        Camera2D(const glm::mat4& ortho);
        Camera2D(const glm::vec2& size);
        Camera2D(int width, int height);

		const glm::mat4 GetViewMatrix() const { return ortho * glm::translate(glm::mat4(1.0f), pos); }
		glm::vec3& GetPos() { return pos; }

        static Camera2D Create(int width, int height);
	};
}
