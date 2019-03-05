#pragma once
#include "glm/glm.hpp"

namespace sgl
{
	struct Light {
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}
