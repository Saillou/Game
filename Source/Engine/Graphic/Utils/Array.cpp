#include "Array.h"

#include "glad/glad.h"

Array::Array() {
	glGenVertexArrays(1, &m_array_id);
}
Array::~Array() {
	glDeleteVertexArrays(1, &m_array_id);
}

void Array::bind() {
	glBindVertexArray(m_array_id);
}

unsigned int Array::getId() const {
	return m_array_id;
}