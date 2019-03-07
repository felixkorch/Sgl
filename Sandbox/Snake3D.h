#pragma once
#include <vector>
#include <memory>
#include "Sgl/Graphics/Mesh.h"
#include "Sgl/Graphics/Model.h"
#include "Sgl/Graphics/Material.h"

using namespace sgl;

class Snake3D {
private:
	unsigned int m_Buffer;
	std::shared_ptr<Mesh> m_Mesh;
	std::vector<Model> m_Models;
	glm::vec3 m_Dir;
public:
	Snake3D(Material& material);

	inline std::vector<Model>& getModels() { return m_Models; };
	void update();
	void setDir(const glm::vec3& dir);
};