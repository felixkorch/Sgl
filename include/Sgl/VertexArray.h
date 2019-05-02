#pragma once
#include "Sgl/VertexBuffer.h"

namespace sgl
{
	class VertexArray {
	private:
		unsigned int rendererID;
		std::vector<VertexBuffer*> buffers;
	public:
		VertexArray();
        VertexArray(VertexArray&& other) = delete;
        VertexArray& operator=(VertexArray&& other) = delete;
        VertexArray(const VertexArray& other) = delete;
        VertexArray& operator=(const VertexArray& other) = delete;
        ~VertexArray();

		void AddBuffer(VertexBuffer* vb, const VertexBufferLayout& layout);
		void Bind() const;
		void Unbind() const;

		VertexBuffer& GetBuffer(int index = 0) { return *buffers[index]; }
		static VertexArray* Create();
	};
}