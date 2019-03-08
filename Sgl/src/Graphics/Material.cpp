#include "Sgl/Graphics/Material.h"
#include "Sgl/Shader.h"
#include "Sgl/Graphics/Texture.h"

#include <vector>
#include <iostream>

namespace sgl
{
	Material::Material(const Shader& shader)
		: shader(shader) {}

	Material::~Material() {}

	void Material::Bind()
	{
		shader.Bind();

		for (unsigned int i = 0; i < textures.size(); i++) {
			textures[i].Bind(i);
			shader.SetUniform1i("u_Slot", i);
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
		textures.emplace_back(texture);
	}

	void Material::BindUniforms()
	{
		shader.SetUniformData(uniformHandler);
	}

}