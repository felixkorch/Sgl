#include "Sgl/Graphics/Material.h"
#include "Sgl/Shader.h"
#include "Sgl/Graphics/Texture2D.h"

#include <vector>
#include <iostream>

namespace sgl
{
	Material::Material() {}
	Material::~Material() {}

    void Material::SetShader(std::unique_ptr<Shader> _shader)
    {
        shader = std::move(_shader);
    }

	void Material::Bind()
	{
		shader->Bind();

		for (unsigned int i = 0; i < textures.size(); i++) {
			textures[i]->Bind(i);
			shader->SetUniform1i("u_Slot", i);
		}
	}

	void Material::Unbind() const
	{
		for (const Texture2D* tex : textures) {
			tex->Unbind();
		}
	}

	void Material::SetTexture(const Texture2D* texture)
	{
		textures.push_back(texture);
	}

	void Material::BindUniforms()
	{
		shader->SetUniformData(uniformHandler);
	}

}