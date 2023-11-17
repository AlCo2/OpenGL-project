#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RendererId);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_RendererId);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
	bind();
	vb.bind();
	const auto& elements = layout.GetElement();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size();i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset+=element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::bind() const{
	glBindVertexArray(m_RendererId);
}
void VertexArray::unbind() const{
	glBindVertexArray(0);
}