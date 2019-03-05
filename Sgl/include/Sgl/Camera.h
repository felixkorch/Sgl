#pragma once
#include "Sgl/Common.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace sgl
{
	class Camera {
	private:
		glm::vec3 m_Position;
		glm::mat4 m_Perspective;
		glm::vec3 m_Forward;
		glm::vec3 m_Up;
	public:
		Camera(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar)
		{
			m_Perspective = glm::perspective(fov, aspect, zNear, zFar);
			m_Position = pos;
			m_Forward = glm::vec3(0.0f, 0.0f, 1.0f);
			m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		}

		glm::mat4 getView() const
		{
			return m_Perspective * glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, -0.5f, 1.0f), m_Up);
		}

		glm::vec3& getPosition() { return m_Position; };
	};
}