#include "Sgl/Graphics/TextureStorage.h"
#include "Sgl/OpenGL.h"

namespace sgl
{
	TextureStorage::TextureStorage()
	{
		glGenTextures(1, &rendererID);
		glBindTexture(GL_TEXTURE_2D, rendererID);
	}

	TextureStorage::~TextureStorage()
	{
		glDeleteTextures(1, &rendererID);
	}

	void TextureStorage::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, rendererID);
	}

	void TextureStorage::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextureStorage::LoadData(unsigned int width, unsigned int height, float* data)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}