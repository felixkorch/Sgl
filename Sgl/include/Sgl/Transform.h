#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

class Transform {
private:
	glm::vec3 translate;
	glm::vec3 rotate;
	glm::vec3 scale;
public:
	Transform(const glm::vec3& translate = glm::vec3(), const glm::vec3& rotate = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
		: translate(translate), rotate(rotate), scale(scale) {}

	inline glm::mat4 getModel() const
	{
		glm::mat4 posMatrix = glm::translate(translate);
		glm::mat4 rotXMatrix = glm::rotate(rotate.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(rotate.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(rotate.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(scale);

		glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	};

	glm::vec3& GetTranslate() { return translate; };
	glm::vec3& GetScale() { return scale; };
	glm::vec3& GetRotate() { return rotate; };
};