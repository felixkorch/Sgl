#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

class Transform {
private:
	glm::vec3 m_Translate;
	glm::vec3 m_Rotate;
	glm::vec3 m_Scale;
public:
	Transform(const glm::vec3& translate = glm::vec3(), const glm::vec3& rotate = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
		: m_Translate(translate), m_Rotate(rotate), m_Scale(scale) {}

	inline glm::mat4 getModel() const
	{
		glm::mat4 posMatrix = glm::translate(m_Translate);
		glm::mat4 rotXMatrix = glm::rotate(m_Rotate.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(m_Rotate.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(m_Rotate.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(m_Scale);

		glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	};

	glm::vec3& GetTranslate() { return m_Translate; };
	glm::vec3& GetScale() { return m_Scale; };
	glm::vec3& GetRotate() { return m_Rotate; };
};