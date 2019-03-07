#pragma once
#include "Sgl/Shader.h"
#include "Sgl/ShaderUniform.h"
#include "Sgl/Graphics/Texture.h"

#include <vector>
#include <iostream>

namespace sgl
{
	class Material {
	private:
		static constexpr auto UniformMaxCount = 20;
		static constexpr auto UniformMaxSize  = 300;

		std::vector<Texture> textures;
		std::vector<UniformDeclaration> uniformDeclarations;
		Shader m_Shader;
		char* m_UniformData;
		unsigned int m_CurrentOffset;
	public:
		Material(const Shader& shader);
		~Material();

		void Bind();
		void Unbind() const;

		void SetTexture(const Texture& texture);
		void BindUniforms();

		void SetLightingData(const Light& lightProperties, float shininess);

		Shader& GetShader()
		{
			return m_Shader;
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
			uniformDeclarations.push_back(ud);
			m_CurrentOffset += sizeof(T);
		}
	};
}