#include "Sgl/OpenGL.h"
#include "Sgl/Common.h"
#include "Sgl/VertexBuffer.h"
#include "Sgl/VertexBufferLayout.h"

namespace sgl
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &rendererID);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void VertexBuffer::InitStaticDraw(const void* data, std::size_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::InitDynamicDraw(std::size_t bufferSize)
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_DYNAMIC_DRAW);
	}

	void VertexBuffer::BindLayout(const VertexBufferLayout& layout)
	{
		const auto& elements = layout.GetElements();
		std::size_t offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
			glEnableVertexAttribArray(i);
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}