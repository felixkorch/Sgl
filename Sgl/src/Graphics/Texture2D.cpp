#include "Sgl/OpenGL.h"
#include "Sgl/Graphics/Texture2D.h"
#include "Sgl/Common.h"
#include "stb_image/stb_image.h"
#include <string>

namespace sgl
{
	Texture2D::Texture2D(const std::string& filePath, TextureParameters params)
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

	Texture2D::Texture2D(unsigned int width, unsigned int height, TextureParameters params)
		: rendererID(0), filePath("NULL"), width(width), height(height), bpp(0), texParams(params)
	{
		glGenTextures(1, &rendererID);
		glBindTexture(GL_TEXTURE_2D, rendererID);

		SetParams(params, nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::SetParams(TextureParameters params, const void* data)
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

	unsigned int Texture2D::GetTextureWrap(TextureWrap wrap)
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

	unsigned int Texture2D::GetTextureFormat(TextureFormat format)
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

	void Texture2D::SetData(void* pixels)
	{
		glBindTexture(GL_TEXTURE_2D, rendererID);
		glTexImage2D(GL_TEXTURE_2D, 0, GetTextureFormat(texParams.format), width, height, 0,
			GetTextureFormat(texParams.format), GL_UNSIGNED_BYTE, pixels);
	}


	void Texture2D::SetColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
	{
		auto data = new std::uint8_t[width * height * 4];
		int i, j;
		for (i = 0; i < width; i++) {
			for (j = 0; j < height; j++) {
				data[i * height * 4 + j * 4 + 0] = r;
				data[i * height * 4 + j * 4 + 1] = g;
				data[i * height * 4 + j * 4 + 2] = b;
				data[i * height * 4 + j * 4 + 3] = a;
			}
		}
		SetData(data);
		delete data;
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &rendererID);
	}

	void Texture2D::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, rendererID);
	}

	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	TextureParameters Texture2D::DefaultParams = { TextureWrap::REPEAT, TextureFormat::RGBA, TextureFilter::NEAREST };
}