#include "Sgl/OpenGL.h"
#include "Sgl/Graphics/Texture2D.h"
#include "stb_image/stb_image.h"
#include <string>

namespace sgl
{
	Texture2D::Texture2D(int width, int height, TextureParameters params)
		: textureHandle(0), params(params), width(width), height(height), bpp(0)
	{
		glGenTextures(1, &textureHandle);
		glBindTexture(GL_TEXTURE_2D, textureHandle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.filter == TextureFilter::LINEAR ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.filter == TextureFilter::LINEAR ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetTextureWrap(params.wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetTextureWrap(params.wrap));
		glTexImage2D(GL_TEXTURE_2D, 0, GetTextureFormat(params.format), width, height, 0,
			GetTextureFormat(params.format), GL_UNSIGNED_BYTE, nullptr);
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
		glBindTexture(GL_TEXTURE_2D, textureHandle);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GetTextureFormat(params.format),
			            GL_UNSIGNED_BYTE, pixels);
	}


	void Texture2D::Resize(int _width, int _height)
	{
		width = _width;
		height = _height;
		glTexImage2D(GL_TEXTURE_2D, 0, GetTextureFormat(params.format), width, height, 0,
			GetTextureFormat(params.format), GL_UNSIGNED_BYTE, nullptr);
	}

	void Texture2D::LoadFromFile(const std::string& fp)
	{
		stbi_set_flip_vertically_on_load(1);
		auto buffer = stbi_load(fp.c_str(), &width, &height, &bpp, 4);
		if (buffer)
			stbi_image_free(buffer);

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GetTextureFormat(params.format),
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
		SetData(data); // Send pixel-data to the GPU
		delete[] data; // Free the temporary memory
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &textureHandle);
	}

	void Texture2D::Bind(unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, textureHandle);
	}

	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D* Texture2D::CreateFromFile(int width, int height, const std::string& filePath, TextureParameters params)
	{
		Texture2D* tex = new Texture2D(width, height, params);
		tex->LoadFromFile(filePath);
		return tex;
	}

	Texture2D* Texture2D::Create(int width, int height, TextureParameters params)
	{
		Texture2D* tex = new Texture2D(width, height, params);
		return tex;
	}

	TextureParameters Texture2D::DefaultParams = { TextureWrap::CLAMP_TO_EDGE, TextureFormat::RGBA, TextureFilter::NEAREST };
}
