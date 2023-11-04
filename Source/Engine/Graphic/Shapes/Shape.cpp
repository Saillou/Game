#include "Shape.h"
#include "glad/glad.h"

Shape::Shape() : m_vbo(GL_ARRAY_BUFFER), m_ebo(GL_ELEMENT_ARRAY_BUFFER) {

}

void Shape::bind() {
    m_vao.bind();
}

void Shape::_bindArray() {
    bind();

    m_vbo.bindData(m_vertices);
    m_ebo.bindData(m_indices);

    _setAttributes();

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Shape::_addPoint(float x, float y, float z) {
    m_vertices.push_back(x);
    m_vertices.push_back(y);
    m_vertices.push_back(z);
}

void Shape::_addTriangle(unsigned int i0, unsigned int i1, unsigned int i2) {
    m_indices.push_back(i0);
    m_indices.push_back(i1);
    m_indices.push_back(i2);
}

void Shape::_addQuad(unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3) {
    m_indices.push_back(i0);
    m_indices.push_back(i1);
    m_indices.push_back(i2);
    m_indices.push_back(i3);
}
