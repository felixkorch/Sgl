#pragma once
#include "Sgl/Common.h"

namespace sgl
{
	class IndexBuffer {
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count)
			:m_Count(count)
		{
			glGenBuffers(1, &m_RendererID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
		}

		~IndexBuffer()
		{
			glDeleteBuffers(1, &m_RendererID);
		}

		void Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		}

		void Unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	};
}