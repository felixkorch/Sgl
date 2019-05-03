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
		unsigned int textureHandle;
		int width, height, bpp;
		TextureParameters params;
		static TextureParameters DefaultParams;

	protected:
        void LoadFromFile(const std::string& fp);
		int GetTextureWrap(TextureWrap wrap);
		int GetTextureFormat(TextureFormat format);
	public:
        Texture2D(int width, int height, TextureParameters params = DefaultParams);
        ~Texture2D();
		void SetColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);
		void SetData(void* pixels);
		void Resize(int _width, int _height);
        void Bind(unsigned int slot);
        void Unbind() const;

        unsigned int GetHandle() { return textureHandle; }
        int GetWidth() { return width; }
        int GetHeight() { return height; }

		static Texture2D* CreateFromFile(int width, int height, const std::string& filePath, TextureParameters params = DefaultParams);
		static Texture2D* Create(int width, int height, TextureParameters params = DefaultParams);
	};
}
