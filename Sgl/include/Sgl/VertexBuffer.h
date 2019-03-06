#pragma once
#include "Sgl/Common.h"

class VertexBuffer {
private:
	unsigned int rendererID;
public:
	VertexBuffer()
	{
		glGenBuffers(1, &rendererID);
}

	~VertexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void Init_StaticDraw(const void* data, std::size_t size) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void Init_DynamicDraw(std::size_t bufferSize) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_DYNAMIC_DRAW);
	}

	void BindAttrib(const VertexBufferLayout& layout)
	{
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
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	}

	void Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};