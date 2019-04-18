#pragma once

namespace sgl
{
	class IndexBuffer {
	private:
		unsigned int rendererID;
		unsigned int count;
	public:
        IndexBuffer();
        IndexBuffer(IndexBuffer&& other);
        IndexBuffer& operator=(IndexBuffer&& other);
        IndexBuffer(const IndexBuffer& other) = delete;
        IndexBuffer& operator=(const IndexBuffer& other) = delete;
        ~IndexBuffer();

		void Load(const unsigned int* data, unsigned int count);
		void Bind() const;
		void Unbind() const;
	};
}