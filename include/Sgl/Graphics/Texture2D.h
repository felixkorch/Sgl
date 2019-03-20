#pragma once
#include <string>

namespace sgl
{
	/*
		CLAMP, CLAMP_TO_BORDER is not supported on embedded so they are commented out for the moment.
	*/

	enum class TextureWrap {
		CLAMP, CLAMP_TO_BORDER, CLAMP_TO_EDGE, REPEAT, MIRRORED_REPEAT
	};

	/*
		RGBA32F is not supported on embedded so they are commented out for the moment.
	*/
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

	class Texture2D {
	private:
		unsigned int rendererID;
		std::string filePath;
		int width, height, bpp;
		TextureParameters texParams;

		static TextureParameters DefaultParams;

	public:
		Texture2D(const std::string& filePath, TextureParameters params = DefaultParams);
        Texture2D(int width, int height, TextureParameters params = DefaultParams);
		~Texture2D();
		Texture2D(const Texture2D&) = delete;
		void operator=(const Texture2D&) = delete;

		void SetData(void* pixels);
		void SetColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);
		void Bind(unsigned int slot) const;
		void Unbind() const;

	private:
        int GetTextureWrap(TextureWrap wrap);
        int GetTextureFormat(TextureFormat format);
		void SetParams(TextureParameters parameters, const void* data);
	};
}
