#pragma once
#include <string>

namespace sgl
{
	enum class TextureWrap {
		CLAMP, CLAMP_TO_BORDER, CLAMP_TO_EDGE, REPEAT, MIRRORED_REPEAT
	};

	enum class TextureFormat {
		RGBA, RGB, RGBA32F, LUMINANCE, LUMINANCE_ALPHA
	};

	enum class TextureFilter {
		NEAREST, LINEAR
	};

	struct TextureParameters {
		TextureWrap wrap;
		TextureFormat format;
		TextureFilter filter;
	};

	class Texture {
	private:
		unsigned int rendererID;
		unsigned char* localBuffer;
		std::string filePath;
		int width, height, bpp;
		TextureParameters texParams;

		static constexpr TextureParameters DefaultParams = { TextureWrap::REPEAT, TextureFormat::RGBA, TextureFilter::LINEAR };

	public:
		Texture(const std::string& filePath, TextureParameters params = DefaultParams);
		Texture(unsigned int width, unsigned int height, TextureParameters parameters);
		~Texture();
		//Texture(const Texture&) = delete;
		//void operator=(const Texture&) = delete;

		void SetData(void* pixels, unsigned int glType);
		void Bind(unsigned int slot) const;
		void Unbind() const;

	private:
		unsigned int GetTextureWrap(TextureWrap wrap);
		unsigned int GetTextureFormat(TextureFormat format);
		void SetParams(TextureParameters parameters, const void* data);
	};
}