#pragma once

namespace sgl
{
	class IndexBuffer {
	private:
		unsigned int rendererID;
		unsigned int count;
	public:
		IndexBuffer();
		~IndexBuffer();
		IndexBuffer(const IndexBuffer&) = delete;
		void operator=(const IndexBuffer&) = delete;

		void Load(const unsigned int* data, unsigned int count);
		void Bind() const;
		void Unbind() const;
	};
}