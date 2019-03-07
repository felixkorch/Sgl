#include "Sgl/Graphics/Material.h"
#include "Sgl/Shader.h"
#include "Sgl/Graphics/Texture.h"

#include <vector>
#include <iostream>

namespace sgl
{
	Material::Material(const Shader& shader)
		: m_Shader(shader), m_CurrentOffset(0), m_UniformData(new char[UniformMaxSize])
	{
		uniformDeclarations.reserve(UniformMaxCount);
	}

	Material::~Material()
	{
		delete[] m_UniformData;
	}

	void Material::Bind()
	{
		m_Shader.Bind();

		for (unsigned int i = 0; i < textures.size(); i++) {
			textures[i].Bind(i);
			m_Shader.SetUniform1i("u_Slot", i);
		}
	}

	void Material::Unbind() const
	{
		for (const Texture& tex : textures) {
			tex.Unbind();
		}
	}

	void Material::SetTexture(const Texture& texture)
	{
		textures.push_back(texture);
	}

	void Material::BindUniforms()
	{
		m_Shader.SetUniformData(uniformDeclarations, m_UniformData);
	}

	void Material::SetLightingData(const Light& lightProperties, float shininess)
	{
		AddUniform<glm::vec3>("u_Material.ambient", lightProperties.ambient);
		AddUniform<glm::vec3>("u_Material.diffuse", lightProperties.diffuse);
		AddUniform<glm::vec3>("u_Material.specular", lightProperties.specular);
		AddUniform<float>("u_Material.shininess", shininess);
	}
}