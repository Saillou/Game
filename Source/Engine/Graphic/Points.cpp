#include "Points.h"

#include "glad/glad.h"

Points::Points(const std::vector<Points::Data>& points) :
    Shape()
{
    // Create
    for (const auto& pt : points) {
        m_vertices.push_back(pt.position.x);
        m_vertices.push_back(pt.position.y);

        m_vertices.push_back(pt.color.r);
        m_vertices.push_back(pt.color.g);
        m_vertices.push_back(pt.color.b);
    }

    // Bind
    _bindArray();
}

void Points::_setAttributes() {
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
}

void Points::draw() {
    glDrawArrays(GL_POINTS, 0, (int)m_vertices.size()/5);
}
