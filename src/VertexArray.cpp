#include "Sgl/OpenGL.h"
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
		for (VertexBuffer* vbo : buffers)
			delete vbo;
	}

	void VertexArray::AddBuffer(VertexBuffer* vb, const VertexBufferLayout& layout)
	{
		Bind();
		vb->Bind();
		const auto& elements = layout.GetElements();
		std::size_t offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
			glEnableVertexAttribArray(i);
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}

		buffers.push_back(vb);
		Unbind();
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(rendererID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	VertexArray* VertexArray::Create()
	{
		return new VertexArray;
	}

}