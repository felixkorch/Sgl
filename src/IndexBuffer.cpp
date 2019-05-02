#include "Sgl/OpenGL.h"
#include "Sgl/IndexBuffer.h"

namespace sgl
{
	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
		: rendererID(0)
		, count(0)
	{
		Load(data, count);
	}

	IndexBuffer::IndexBuffer()
		: rendererID(0)
		, count(0)
	{}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void IndexBuffer::Load(const unsigned int* data, unsigned int count)
	{
		glGenBuffers(1, &rendererID);
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

	IndexBuffer* IndexBuffer::Create(const unsigned int* data, unsigned int count)
	{
		return new IndexBuffer(data, count);
	}

}