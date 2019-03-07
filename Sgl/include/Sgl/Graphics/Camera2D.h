#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace sgl
{
	class Camera2D {
	private:
		glm::mat4 ortho;
		glm::vec3 pos;
	public:
		Camera2D(const glm::mat4& ortho)
			: pos(glm::vec3()), ortho(ortho) {}

		void Move(const glm::vec3& vec) { pos += vec; };
		const glm::mat4 GetViewMatrix() const { return ortho * glm::translate(glm::mat4(1.0f), pos); };
	};
}
