#pragma once
#include "Sgl/VertexBufferLayout.h"

namespace sgl
{
	enum class BufferUsage {
		DYNAMIC, STATIC
	};

	class VertexBuffer {
	private:
		unsigned int rendererID;
		std::size_t bufferSize;
	protected:
        VertexBuffer(VertexBuffer&& other);
        VertexBuffer& operator=(VertexBuffer&& other);
        VertexBuffer(const VertexBuffer& other);
        VertexBuffer& operator=(const VertexBuffer& other);
	public:
		VertexBuffer();
        ~VertexBuffer();
		void BindLayout(const VertexBufferLayout& layout);
		void Bind() const;
		void Unbind() const;
		void* GetInternalPointer();
		void ReleasePointer();
		void InitStaticBufferUsage(const void* data, std::size_t size);
		void InitDynamicBufferUsage(std::size_t size);

		template<BufferUsage Usage> static VertexBuffer* Create(const void* data, std::size_t size);
		template<BufferUsage Usage> static VertexBuffer* Create(std::size_t bufferSize);
	};

	template <>
	inline VertexBuffer* VertexBuffer::Create<BufferUsage::STATIC>(const void* data, std::size_t size)
	{
		VertexBuffer* vbo = new VertexBuffer;
		vbo->InitStaticBufferUsage(data, size);
		return vbo;
	}

	template<>
	inline VertexBuffer* VertexBuffer::Create<BufferUsage::DYNAMIC>(std::size_t bufferSize)
	{
		VertexBuffer* vbo = new VertexBuffer;
		vbo->InitDynamicBufferUsage(bufferSize);
		return vbo;
	}
}