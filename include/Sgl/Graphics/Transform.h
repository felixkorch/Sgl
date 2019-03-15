#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

class Transform {
public:
	glm::vec3 translate;
	glm::vec3 rotate;
	glm::vec3 scale;

	constexpr Transform(const glm::vec3& translate = glm::vec3(), const glm::vec3& rotate = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
		: translate(translate), rotate(rotate), scale(scale) {}

	glm::mat4 GetModelMatrix() const
	{
		const glm::mat4 posMatrix = glm::translate(translate);
		const glm::mat4 rotXMatrix = glm::rotate(rotate.x, glm::vec3(1, 0, 0));
		const glm::mat4 rotYMatrix = glm::rotate(rotate.y, glm::vec3(0, 1, 0));
		const glm::mat4 rotZMatrix = glm::rotate(rotate.z, glm::vec3(0, 0, 1));
		const glm::mat4 scaleMatrix = glm::scale(scale);
		const glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	};
};