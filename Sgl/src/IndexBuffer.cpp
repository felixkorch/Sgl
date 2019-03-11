#include "Sgl/OpenGL.h"
#include "Sgl/IndexBuffer.h"

namespace sgl
{
	IndexBuffer::IndexBuffer()
		: rendererID(0), count(0)
	{
		glGenBuffers(1, &rendererID);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void IndexBuffer::Init(const unsigned int* data, unsigned int count)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}