#include "Quad.hpp"
#include "glad/glad.h"

#include <glm/gtc/constants.hpp>

Quad::Quad() : BaseShape()
{
    // Create 4 points
    _addPoint(-1.95f, -1.95f, 0.0f);
    _addPoint(-1.95f, +1.95f, 0.0f);
    _addPoint(+1.95f, +1.95f, 0.0f);
    _addPoint(+1.95f, -1.95f, 0.0f);

    _addAsQuad(0, 1, 2, 3);

    // Bind
    _bindArray();
}

void Quad::_setAttributes() {
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
}

void Quad::draw() {
    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glDrawElements(GL_PATCHES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
}
