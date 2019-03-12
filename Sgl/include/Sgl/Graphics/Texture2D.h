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

	class Texture2D {
	private:
		unsigned int rendererID;
		std::string filePath;
		int width, height, bpp;
		TextureParameters texParams;

		static TextureParameters DefaultParams;

	public:
		Texture2D(const std::string& filePath, TextureParameters params = DefaultParams);
		Texture2D(unsigned int width, unsigned int height, TextureParameters params = DefaultParams);
		~Texture2D();
		Texture2D(const Texture2D&) = delete;
		void operator=(const Texture2D&) = delete;

		void SetData(void* pixels);
		void Bind(unsigned int slot) const;
		void Unbind() const;

	private:
		unsigned int GetTextureWrap(TextureWrap wrap);
		unsigned int GetTextureFormat(TextureFormat format);
		void SetParams(TextureParameters parameters, const void* data);
	};
}