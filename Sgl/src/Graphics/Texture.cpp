#include "Sgl/OpenGL.h"
#include "Sgl/Graphics/Texture.h"
#include "Sgl/Common.h"
#include "stb_image/stb_image.h"
#include <string>

namespace sgl
{
	Texture::Texture(const std::string& filePath, TextureParameters params)
		: rendererID(0), filePath(filePath), width(0), height(0), bpp(0), texParams(params)
	{
		stbi_set_flip_vertically_on_load(1);
		auto localBuffer = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);

		glGenTextures(1, &rendererID);
		glBindTexture(GL_TEXTURE_2D, rendererID);

		SetParams(params, localBuffer);

		glBindTexture(GL_TEXTURE_2D, 0);

		if (localBuffer)
			stbi_image_free(localBuffer);
	}

	Texture::Texture(unsigned int width, unsigned int height, TextureParameters params)
		: rendererID(0), filePath("NULL"), width(width), height(height), bpp(0), texParams(params)
	{
		glGenTextures(1, &rendererID);
		glBindTexture(GL_TEXTURE_2D, rendererID);

		SetParams(params, nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::SetParams(TextureParameters params, const void* data)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.filter == TextureFilter::LINEAR ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.filter == TextureFilter::LINEAR ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetTextureWrap(params.wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetTextureWrap(params.wrap));

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GetTextureFormat(params.format),
				width, height, 0, GetTextureFormat(params.format), GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	unsigned int Texture::GetTextureWrap(TextureWrap wrap)
	{
		switch (wrap) {
		//case TextureWrap::CLAMP:			return GL_CLAMP;
		//case TextureWrap::CLAMP_TO_BORDER:	return GL_CLAMP_TO_BORDER;
		case TextureWrap::CLAMP_TO_EDGE:	return GL_CLAMP_TO_EDGE;
		case TextureWrap::REPEAT:			return GL_REPEAT;
		case TextureWrap::MIRRORED_REPEAT:	return GL_MIRRORED_REPEAT;
		}
		return 0;
	}

	unsigned int Texture::GetTextureFormat(TextureFormat format)
	{
		switch (format) {
		case TextureFormat::RGBA:				return GL_RGBA;
		case TextureFormat::RGB:				return GL_RGB;
		//case TextureFormat::RGBA32F:			return GL_RGBA32F;
		case TextureFormat::LUMINANCE:			return GL_LUMINANCE;
		case TextureFormat::LUMINANCE_ALPHA:	return GL_LUMINANCE_ALPHA;
		}
		return 0;
	}

	void Texture::SetData(void* pixels, unsigned int glType)
	{
		glBindTexture(GL_TEXTURE_2D, rendererID);
		glTexImage2D(GL_TEXTURE_2D, 0, GetTextureFormat(texParams.format), width, height, 0,
			GetTextureFormat(texParams.format), glType, pixels);
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

	TextureParameters Texture::DefaultParams = { TextureWrap::REPEAT, TextureFormat::RGBA, TextureFilter::LINEAR };
}