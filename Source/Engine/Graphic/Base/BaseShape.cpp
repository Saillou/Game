#include "BaseShape.hpp"
#include "glad/glad.h"

BaseShape::BaseShape() : m_vbo(GL_ARRAY_BUFFER), m_ebo(GL_ELEMENT_ARRAY_BUFFER) {

}

void BaseShape::bind() {
    m_vao.bind();
}

int BaseShape::indicesLength() const {
    return (int)m_indices.size();
}

int BaseShape::verticesLength() const {
    return (int)m_vertices.size();
}

void BaseShape::_bindArray() {
    bind();

    m_vbo.bindData(m_vertices);
    m_ebo.bindData(m_indices);

    _setAttributes();

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseShape::_addPoint(float x, float y, float z) {
    m_vertices.push_back(x);
    m_vertices.push_back(y);
    m_vertices.push_back(z);
}

void BaseShape::_addPoint(const glm::vec3& vec) {
    _addPoint(vec.x, vec.y, vec.z);
}

void BaseShape::_addAsLine(unsigned int i0, unsigned int i1) {
    m_indices.push_back(i0);
    m_indices.push_back(i1);
}

void BaseShape::_addAsTriangle(unsigned int i0, unsigned int i1, unsigned int i2) {
    m_indices.push_back(i0);
    m_indices.push_back(i1);
    m_indices.push_back(i2);
}

void BaseShape::_addAsQuad(unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3) {
    m_indices.push_back(i0);
    m_indices.push_back(i1);
    m_indices.push_back(i2);
    m_indices.push_back(i3);
}
