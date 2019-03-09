#include "Sgl/OpenGL.h"
#include "Sgl/Graphics/Texture.h"
#include "Sgl/Common.h"
#include "stb_image/stb_image.h"
#include <string>

namespace sgl
{
	Texture::Texture(const std::string& filePath)
		: rendererID(0), filePath(filePath), localBuffer(nullptr),
		width(0), height(0), bpp(0)
	{
		stbi_set_flip_vertically_on_load(1);
		localBuffer = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);

		glGenTextures(1, &rendererID);
		glBindTexture(GL_TEXTURE_2D, rendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// clamp_to_edge?
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (localBuffer)
			stbi_image_free(localBuffer);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &rendererID);
	}

	void Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, rendererID);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}