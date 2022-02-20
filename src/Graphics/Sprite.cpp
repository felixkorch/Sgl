#include "Sgl/Graphics/Sprite.h"

namespace sgl {

	void Sprite::FromTexture(std::shared_ptr<Texture2D> texture, int width, int height)
	{
		if (width == 0)
			width = texture->GetWidth();

		if (height == 0)
			height = texture->GetHeight();

		size = glm::vec2(width, height);
		this->texture = texture;
	}

	void Sprite::FromColor(glm::vec4 color, int width, int height)
	{
		size = glm::vec2(width, height);
		this->color = color;
	}
}