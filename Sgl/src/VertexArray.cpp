#include "Sgl/VertexArray.h"
#include "Sgl/VertexBufferLayout.h"

namespace sgl
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &rendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		Bind();
		vb.Bind();
		const auto& elements = layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
			glEnableVertexAttribArray(i);
			offset += element.count * VertexBufferElement::getSizeOfType(element.type);
		}
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(rendererID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
}