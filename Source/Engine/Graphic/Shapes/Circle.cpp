#include "Circle.h"
#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

Circle::Circle(float radius) :
    Shape(),
    m_radius(radius)
{
    // Create
    const int N = (int)round(5 * glm::pow(3, glm::log2(100.0f * radius) / glm::log2(10.0f)));
    const float dtheta =  2.0f * glm::pi<float>()/ N;

    float xi = radius;
    float yi = 0;
   
    _addPoint(0, 0, 0);
    _addPoint(xi, yi, 0);
    for (int i = 0; i <= N; i++) {
        xi = radius * glm::cos(dtheta * i);
        yi = radius * glm::sin(dtheta * i);
        _addPoint(xi, yi, 0);
        _addAsTriangle(0, i+1, i+2);
    }

    // Bind
    _bindArray();
}

void Circle::_setAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

void Circle::draw() {
    glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
}
