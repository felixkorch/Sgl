/*
#include "Snake3D.h"
#define TILE_SIZE 0.36f

Snake3D::Snake3D(Material& material)
	: m_Buffer(15), m_Mesh(std::make_shared<Mesh>("res/smallercube.obj", material))
{
	m_Models.reserve(50);

	for (unsigned int i = 0; i < 5; i++) {
		m_Models.emplace_back(m_Mesh);
		m_Models[i].GetTransform().translate.x = TILE_SIZE * (i + 1);
	}

	m_Dir = glm::vec3(-1, 0, 0);
}

void Snake3D::update()
{
	if (m_Buffer--)
		return;

	for (unsigned int i = m_Models.size() - 1; i > 0; i--)
		m_Models[i].GetTransform().translate = m_Models[i - 1].GetTransform().translate;

	m_Models.front().GetTransform().translate += TILE_SIZE * m_Dir;
	m_Buffer = 15;
}

void Snake3D::setDir(const glm::vec3& dir)
{
	m_Dir = dir;
}*/