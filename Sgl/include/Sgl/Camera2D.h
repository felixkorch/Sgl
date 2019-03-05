#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace sgl
{
	class Camera2D {
	private:
		glm::mat4 m_Ortho;
		glm::vec3 m_Pos;
	public:
		Camera2D(const glm::mat4& ortho)
			: m_Pos(glm::vec3()), m_Ortho(ortho) {}

		void Move(const glm::vec3& vec) { m_Pos += vec; };
		const glm::mat4 GetViewMatrix() const { return m_Ortho * glm::translate(glm::mat4(1.0f), m_Pos); };
	};
}
