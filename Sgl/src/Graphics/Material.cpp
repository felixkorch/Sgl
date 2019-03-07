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

	template <>
	void Material::AddUniform<int>(const std::string& name, const int& val)
	{
		*(int*)(m_UniformData + m_CurrentOffset) = val;
		uniformDeclarations.push_back({ m_CurrentOffset, UniformType::Int, name });
		m_CurrentOffset += sizeof(int);
	}

	template <>
	void Material::AddUniform<float>(const std::string& name, const float& val)
	{
		*(float*)(m_UniformData + m_CurrentOffset) = val;
		uniformDeclarations.push_back({ m_CurrentOffset, UniformType::Float, name });
		m_CurrentOffset += sizeof(float);
	}

	template <>
	void Material::AddUniform<glm::vec3>(const std::string& name, const glm::vec3& val)
	{
		*(glm::vec3*)(m_UniformData + m_CurrentOffset) = val;
		uniformDeclarations.push_back({ m_CurrentOffset, UniformType::Vec3, name });
		m_CurrentOffset += sizeof(glm::vec3);
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

	/*void Material::SetLightingData(const Light& lightProperties, float shininess)
	{
		AddUniform<glm::vec3>("u_Material.ambient", lightProperties.ambient);
		AddUniform<glm::vec3>("u_Material.diffuse", lightProperties.diffuse);
		AddUniform<glm::vec3>("u_Material.specular", lightProperties.specular);
		AddUniform<float>("u_Material.shininess", shininess);
	}*/

	void Material::SetLightingData(const LightingData& data)
	{
		AddUniform<glm::vec3>("u_Material.ambient", data.ambient);
		AddUniform<glm::vec3>("u_Material.diffuse", data.diffuse);
		AddUniform<glm::vec3>("u_Material.specular", data.specular);
		AddUniform<float>("u_Material.shininess", data.shininess);
	}

}