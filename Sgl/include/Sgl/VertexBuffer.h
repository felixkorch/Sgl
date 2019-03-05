#pragma once
#include "Sgl/Common.h"

class VertexBuffer {
private:
	unsigned int m_RendererID;
public:
	VertexBuffer()
	{
		glGenBuffers(1, &m_RendererID);
}

	~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void Init_StaticDraw(const void* data, unsigned int size) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void Init_DynamicDraw(unsigned int bufferSize) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_DYNAMIC_DRAW);
	}

	void Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};