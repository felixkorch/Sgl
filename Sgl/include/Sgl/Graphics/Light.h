#pragma once
#include "glm/glm.hpp"

namespace sgl
{
	struct LightingData {
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;

		LightingData()
			: ambient(glm::vec3(1.0, 1.0, 1.0)),
			diffuse(glm::vec3(1.0, 1.0, 1.0)),
			specular(glm::vec3(1.0, 1.0, 1.0)),
			shininess(32.0f) {}

		LightingData(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
			: ambient(ambient),
			diffuse(diffuse),
			specular(specular),
			shininess(shininess) {}
	};

	struct Light {
		glm::vec3 position;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}
