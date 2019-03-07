#pragma once
#include "Sgl/VertexBufferLayout.h"

namespace sgl
{
	class VertexBuffer {
	private:
		unsigned int rendererID;
	public:
		VertexBuffer();
		~VertexBuffer();

		void Init_StaticDraw(const void* data, std::size_t size);
		void Init_DynamicDraw(std::size_t bufferSize);
		void BindAttrib(const VertexBufferLayout& layout);
		void Bind() const;
		void Unbind() const;
	};
}