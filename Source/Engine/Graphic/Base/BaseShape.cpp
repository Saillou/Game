#include "BaseShape.hpp"
#include "glad/glad.h"

BaseShape::BaseShape() : 
    m_vbo_vertices(GL_ARRAY_BUFFER), 
    m_vbo_normals(GL_ARRAY_BUFFER), 
    m_ebo(GL_ELEMENT_ARRAY_BUFFER) 
{
    // ..
}

void BaseShape::createBatch(const std::vector<glm::mat4>& models) {
    Buffer planets_buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    planets_buffer.bindData(models);

    bind();

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    unbind();
}

void BaseShape::bind() {
    m_vao.bind();
}

void BaseShape::unbind() {
    m_vao.unbind();
}

int BaseShape::indicesLength() const {
    return (int)m_indices.size();
}

int BaseShape::verticesLength() const {
    return (int)m_vertices.size();
}

int BaseShape::normalsLength() const {
    return (int)m_normals.size();
}

void BaseShape::_bindArray() {
    bind();

    m_vbo_vertices.bindData(m_vertices);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    m_vbo_normals.bindData(m_normals);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    m_ebo.bindData(m_indices);

    // unbind arrays
    m_vbo_vertices.unbind();
    m_vbo_normals.unbind();
}

// Helpers
int BaseShape::_addPoint(float x, float y, float z) {
    m_vertices.push_back(x);
    m_vertices.push_back(y);
    m_vertices.push_back(z);

    return verticesLength() / 3 - 1;
}

int BaseShape::_addPoint(float x, float y, float z, float nx, float ny, float nz) {
    m_normals.push_back(nx);
    m_normals.push_back(ny);
    m_normals.push_back(nz);

    return _addPoint(x, y, z);
}

int BaseShape::_addPoint(const glm::vec3& vec) {
    return _addPoint(vec.x, vec.y, vec.z);
}

int BaseShape::_addPoint(const glm::vec3& vec, const glm::vec3& norm) {
    return _addPoint(
        vec.x,  vec.y,  vec.z, 
        norm.x, norm.y, norm.z
    );
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
