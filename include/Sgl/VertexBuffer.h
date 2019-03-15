#pragma once
#include "Sgl/VertexBufferLayout.h"

namespace sgl
{
	class VertexBuffer {
	private:
		unsigned int rendererID;
	public:
		VertexBuffer();
		VertexBuffer(const VertexBuffer&) = delete;
		void operator=(const VertexBuffer&) = delete;
		~VertexBuffer();

		void InitStaticDraw(const void* data, std::size_t size);
		void InitDynamicDraw(std::size_t bufferSize);
		void BindLayout(const VertexBufferLayout& layout);
		void Bind() const;
		void Unbind() const;
	};
}