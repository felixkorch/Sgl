#pragma once
#include "Sgl/Common.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace sgl
{
	class Camera {
	private:
		glm::vec3 position;
		glm::mat4 perspective;
		glm::vec3 forward;
		glm::vec3 up;
	public:
		Camera(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar)
		{
			perspective = glm::perspective(fov, aspect, zNear, zFar);
			position = pos;
			forward = glm::vec3(0.0f, 0.0f, 1.0f);
			up = glm::vec3(0.0f, 1.0f, 0.0f);
		}

		glm::mat4 GetView() const
		{
			return perspective * glm::lookAt(position, position + glm::vec3(0, -0.5, 1), up);
		}

		glm::vec3& GetPosition() { return position; };
	};
}