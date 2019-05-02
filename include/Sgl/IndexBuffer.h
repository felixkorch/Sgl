#pragma once

namespace sgl
{
	class IndexBuffer {
	private:
		unsigned int rendererID;
		unsigned int count;
	protected:
		IndexBuffer(IndexBuffer&& other);
		IndexBuffer& operator=(IndexBuffer&& other);
		IndexBuffer(const IndexBuffer& other);
		IndexBuffer& operator=(const IndexBuffer& other);
	public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        IndexBuffer();
        ~IndexBuffer();

		void Bind() const;
		void Unbind() const;
		void Load(const unsigned int* data, unsigned int count);

		static IndexBuffer* Create(const unsigned int* data, unsigned int count);
	};
}