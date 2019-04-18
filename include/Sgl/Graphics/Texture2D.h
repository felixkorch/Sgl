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
		Texture2D(TextureParameters params = DefaultParams);
        Texture2D(int width, int height, TextureParameters params = DefaultParams);
        Texture2D(Texture2D&& other);
        Texture2D& operator=(Texture2D&& other);
        Texture2D(const Texture2D& other) = delete;
        Texture2D& operator=(const Texture2D& other) = delete;
        ~Texture2D();

		void SetData(void* pixels);
		void SetSize(int _width, int _height);
		void SetParams(TextureParameters parameters);
        void LoadFromFile(const std::string& fp);
		void SetColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);
		void Bind(unsigned int slot) const;
		void Unbind() const;

	private:
        int GetTextureWrap(TextureWrap wrap);
        int GetTextureFormat(TextureFormat format);
	};
}
