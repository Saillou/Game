#include "Square.h"

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

Square::Square(float side) : 
	Shape(),
	m_side(side)
{
    // Create
    _addPoint(-side,  side, 0.0f);
    _addPoint( side, -side, 0.0f);
    _addPoint( side,  side, 0.0f);
    _addPoint(-side, -side, 0.0f);

    _addTriangle(1, 2, 3);
    _addTriangle(3, 2, 0);

    // Bind
    _bindArray();
}

void Square::_setAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

void Square::draw() {
    glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
}
