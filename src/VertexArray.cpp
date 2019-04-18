#include "Sgl/OpenGL.h"
#include "Sgl/VertexArray.h"
#include "Sgl/VertexBufferLayout.h"
#include "Sgl/Common.h"

namespace sgl
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &rendererID);
	}

    VertexArray::VertexArray(VertexArray&& other)
        : rendererID(other.rendererID)
    {
        other.rendererID = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& other)
    {
        rendererID = other.rendererID;
        other.rendererID = 0;
        return *this;
    }

    VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		Bind();
		vb.Bind();
		const auto& elements = layout.GetElements();
		std::size_t offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
			glEnableVertexAttribArray(i);
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
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