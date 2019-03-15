#pragma once
#include "Sgl/VertexBuffer.h"

namespace sgl
{
	class VertexArray {
	private:
		unsigned int rendererID;
	public:
		VertexArray();
		VertexArray(const VertexArray&) = delete;
		void operator=(const VertexArray&) = delete;
		~VertexArray();
		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		void Bind() const;
		void Unbind() const;
	};
}