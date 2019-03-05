#pragma once
#include "Sgl/VertexBuffer.h"
#include "Sgl/VertexBufferLayout.h"

class VertexBufferLayout;

class VertexArray {
private:
	unsigned int m_RendererID;
public:

	VertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		Bind();
		vb.Bind();
		const auto& elements = layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
			offset += element.count * VertexBufferElement::getSizeOfType(element.type);
		}
	}

	void Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void Unbind() const
	{
		glBindVertexArray(0);
	}
};