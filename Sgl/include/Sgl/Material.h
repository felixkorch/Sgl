#pragma once
#include "Sgl/Shader.h"
#include "Sgl/Texture.h"

#include <vector>
#include <iostream>

namespace sgl
{
	class Material {
	private:
		static constexpr auto UniformMaxCount = 20;
		static constexpr auto UniformMaxSize  = 300;

		std::vector<Texture> m_Textures;
		std::vector<UniformDeclaration> m_UniformDeclarations;
		Shader m_Shader;
		char* m_UniformData;
		unsigned int m_CurrentOffset;
	public:


		Material(const Shader& shader)
			: m_Shader(shader), m_CurrentOffset(0), m_UniformData(new char[UniformMaxSize])
		{
			m_UniformDeclarations.reserve(UniformMaxCount);
		}

		~Material()
		{
			delete[] m_UniformData;
		}

		void Bind()
		{
			m_Shader.Bind();

			for (unsigned int i = 0; i < m_Textures.size(); i++) {
				m_Textures[i].Bind(i);
				m_Shader.SetUniform1i("u_Slot", i);
			}
		}

		void Unbind() const
		{
			for (const Texture& tex : m_Textures) {
				tex.Unbind();
			}
		}

		void SetTexture(const Texture& texture)
		{
			m_Textures.push_back(texture);
		}

		void BindUniforms()
		{
			m_Shader.SetUniformData(m_UniformDeclarations, m_UniformData);
		}

		template <class T>
		void AddUniform(const std::string& name, T val)
		{
			UniformDeclaration ud;

			if (std::is_same<T, int>::value)
				ud = { m_CurrentOffset, UniformType::Int, name };
			else if (std::is_same<T, glm::vec3>::value)
				ud = { m_CurrentOffset, UniformType::Vec3, name };
			else if (std::is_same<T, float>::value)
				ud = { m_CurrentOffset, UniformType::Float, name };

			*((T*)(m_UniformData + m_CurrentOffset)) = val;
			m_UniformDeclarations.push_back(ud);
			m_CurrentOffset += sizeof(T);
		}

		void SetLightingData(const Light& lightProperties, float shininess)
		{
			AddUniform<glm::vec3>("u_Material.ambient", lightProperties.ambient);
			AddUniform<glm::vec3>("u_Material.diffuse", lightProperties.diffuse);
			AddUniform<glm::vec3>("u_Material.specular", lightProperties.specular);
			AddUniform<float>("u_Material.shininess", shininess);
		}


		Shader& GetShader()
		{
			return m_Shader;
		}
	};
}