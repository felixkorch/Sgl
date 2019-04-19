#include "Sgl/OpenGL.h"
#include "Sgl/Graphics/Texture2D.h"
#include "stb_image/stb_image.h"
#include <string>

namespace sgl
{
	Texture2D::Texture2D(TextureParameters params)
		: rendererID(0), filePath("NULL"), width(0), height(0), bpp(0), texParams(params)
	{
		glGenTextures(1, &rendererID);
		SetParams(params);
	}

    Texture2D::Texture2D(int width, int height, TextureParameters params)
		: rendererID(0), filePath("NULL"), width(width), height(height), bpp(0), texParams(params)
	{
		glGenTextures(1, &rendererID);
		SetParams(params);
	}

    Texture2D::Texture2D(Texture2D&& other)
        : rendererID(other.rendererID)
        , filePath(other.filePath)
        , bpp(other.bpp)
        , width(other.width)
        , height(other.height)
        , texParams(other.texParams)
    {
        other.rendererID = 0;
    }

    Texture2D& Texture2D::operator=(Texture2D&& other)
    {
        rendererID = other.rendererID;
        filePath = other.filePath;
        bpp = other.bpp;
        width = other.width;
        height = other.height;
        texParams = other.texParams;
        other.rendererID = 0;
        return *this;
    }

    void Texture2D::SetParams(TextureParameters params)
	{
		// Bind the texture
		glBindTexture(GL_TEXTURE_2D, rendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.filter == TextureFilter::LINEAR ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.filter == TextureFilter::LINEAR ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetTextureWrap(params.wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetTextureWrap(params.wrap));
        glTexImage2D(GL_TEXTURE_2D, 0, GetTextureFormat(texParams.format), width, height, 0,
                     GetTextureFormat(texParams.format), GL_UNSIGNED_BYTE, nullptr);
		// Unbind the texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

    int Texture2D::GetTextureWrap(TextureWrap wrap)
	{
		switch (wrap) {
		case TextureWrap::CLAMP_TO_EDGE:	return GL_CLAMP_TO_EDGE;
		case TextureWrap::REPEAT:			return GL_REPEAT;
		case TextureWrap::MIRRORED_REPEAT:	return GL_MIRRORED_REPEAT;
		}
		return 0;
	}

    int Texture2D::GetTextureFormat(TextureFormat format)
	{
		switch (format) {
		case TextureFormat::RGBA:				return GL_RGBA;
		case TextureFormat::RGB:				return GL_RGB;
		case TextureFormat::LUMINANCE:			return GL_LUMINANCE;
		case TextureFormat::LUMINANCE_ALPHA:	return GL_LUMINANCE_ALPHA;
		}
		return 0;
	}

	void Texture2D::SetData(void* pixels)
	{
		glBindTexture(GL_TEXTURE_2D, rendererID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GetTextureFormat(texParams.format),
			            GL_UNSIGNED_BYTE, pixels);
	}


	void Texture2D::SetSize(int _width, int _height)
	{
		width = _width;
		height = _height;
	}

	void Texture2D::LoadFromFile(const std::string& fp)
	{
		stbi_set_flip_vertically_on_load(1);
		auto buffer = stbi_load(fp.c_str(), &width, &height, &bpp, 4);
		if (buffer)
			stbi_image_free(buffer);

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GetTextureFormat(texParams.format),
            GL_UNSIGNED_BYTE, buffer);
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
        delete[] data;
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

	TextureParameters Texture2D::DefaultParams = { TextureWrap::CLAMP_TO_EDGE, TextureFormat::RGBA, TextureFilter::NEAREST };
}
