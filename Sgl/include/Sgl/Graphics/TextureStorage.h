#pragma once

namespace sgl
{
	class TextureStorage {
	private:
		unsigned int rendererID;
		float* buffer;
	public:
		TextureStorage();
		~TextureStorage();

		void Bind(unsigned int slot) const;
		void Unbind() const;
		void LoadData(unsigned int width, unsigned int height, float* data);
	};
}