#pragma once
#include <string>

namespace sgl
{
	class Texture {
	private:
		unsigned int rendererID;
		unsigned char* localBuffer;
		std::string filePath;
		int width, height, bpp;

	public:
		Texture(const std::string& filePath);
		~Texture();
		void Bind(unsigned int slot) const;

		void Unbind() const;
	};
}