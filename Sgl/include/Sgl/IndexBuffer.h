#pragma once
#include "Sgl/Common.h"

namespace sgl
{
	class IndexBuffer {
	private:
		unsigned int rendererID;
		unsigned int count;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count)
			:count(count)
		{
			glGenBuffers(1, &rendererID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
		}

		~IndexBuffer()
		{
			glDeleteBuffers(1, &rendererID);
		}

		void Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
		}

		void Unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	};
}