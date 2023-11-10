#include "Fruit.hpp"

Fruit::_FruitShape::_FruitShape(float radius) {
    const float width = radius;
    const float height = radius;

    constexpr float dtheta = glm::pi<float>() / 20.0f;
    constexpr int N_POINTS = (int)(2.0f * glm::pi<float>() / dtheta);

    // start
    float xi = width / 2;
    float yi = 0;

    _addPoint(0, 0, 0);    // center
    _addPoint(xi, 0, yi);  // first point

    // then, put points on the border of the ellipse
    for (int i = 0; i <= N_POINTS; i++) {
        xi = width / 2 * glm::cos(dtheta * i);
        yi = height / 2 * glm::sin(dtheta * i);
        _addPoint(xi, 0.0f, yi);
        _addAsTriangle(0, i+1, i+2); // all triangles start from the center
    }

    // Bind
    _bindArray();
}

void Fruit::_FruitShape::draw() {
    glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
}

void Fruit::_FruitShape::_setAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}


Fruit::Fruit(float radius) {
    m_fruit = std::make_shared<_FruitShape>(radius);

    m_shader
        .attachSource(GL_VERTEX_SHADER, ShaderSource{}
            .add_var("in", "vec3", "aPos")
            .add_var("uniform", "vec3", "offset")
            .add_var("uniform", "mat4", "Projection")
            .add_var("uniform", "mat4", "Modelview")
            .add_func("void", "main", "", R"_main_(
                gl_Position = Projection * Modelview * vec4(aPos + offset, 1.0);
            )_main_").str()
        )
        .attachSource(GL_FRAGMENT_SHADER, ShaderSource{}
            .add_var("uniform", "vec3", "color")
            .add_var("uniform", "float", "alpha")
            .add_var("out", "vec4", "FragColor")
            .add_func("void", "main", "", R"_main_(
                FragColor = vec4(color, alpha);
            )_main_").str()
        )
        .link();
}

void Fruit::draw(const Camera& camera, const glm::vec3& pos) {
    m_shader
        .use()
        .set("offset", pos.x, pos.y, pos.z)
        .set("color", 0.2f, 0.9f, 0.8f)
        .set("alpha", 1.0f)
        .set("Projection", camera.projection)
        .set("Modelview", camera.modelview);

    m_fruit->bind();
    m_fruit->draw();
}
