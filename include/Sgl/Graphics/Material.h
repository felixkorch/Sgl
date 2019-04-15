#pragma once
#include "Sgl/Shader.h"
#include "Sgl/ShaderUniform.h"
#include "Sgl/Graphics/Texture2D.h"

#include <vector>
#include <iostream>

namespace sgl
{
	class Material {
	private:
		std::unique_ptr<Shader> shader;
		std::vector<const Texture2D*> textures;
		UniformHandler uniformHandler;
	public:
		Material();
        Material(const Material& other) = delete;
        Material& operator=(const Material& other) = delete;
        Material(Material&& other) = default;
		~Material();

		void Bind();
		void Unbind() const;
		void BindUniforms();
		void SetTexture(const Texture2D* texture);
        void SetShader(std::unique_ptr<Shader> _shader);

		Shader& GetShader()
		{
			return *shader;
		}

		template <class T>
		void AddUniform(const char* name, T val)
		{
			uniformHandler.AddUniform(UniformHandler::Uniform<T>{ name, val });
		}
	};
}