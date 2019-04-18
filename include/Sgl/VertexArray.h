#pragma once
#include "Sgl/VertexBuffer.h"

namespace sgl
{
	class VertexArray {
	private:
		unsigned int rendererID;
	public:
		VertexArray();
        VertexArray(VertexArray&& other);
        VertexArray& operator=(VertexArray&& other);
        VertexArray(const VertexArray& other) = delete;
        VertexArray& operator=(const VertexArray& other) = delete;
        ~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		void Bind() const;
		void Unbind() const;
	};
}