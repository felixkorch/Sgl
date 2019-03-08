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
		Shader shader;
		std::vector<Texture> textures;
		UniformHandler uniformHandler;
	public:
		Material(const Shader& shader);
		~Material();

		void Bind();
		void Unbind() const;
		void BindUniforms();
		void SetTexture(const Texture& texture);

		Shader& GetShader()
		{
			return shader;
		}

		template <class T>
		void AddUniform(const char* name, T val)
		{
			uniformHandler.AddUniform(UniformHandler::Uniform<T>{ name, val });
		}
	};
}