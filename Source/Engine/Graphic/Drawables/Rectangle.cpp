#include "Rectangle.hpp"

#include <sstream>
#include <vector>
#include <utility>
#include <unordered_map>

// -------- Public Rectangle Helper - Static --------
void Rectangle::Draw(glm::vec3 pos, glm::vec2 size, glm::vec4 color) {
    // Get the needed shape
    Rectangle rectangle(pos, size, color);
    const auto& shape = _Get_Or_Create([=] {
        return std::make_shared<Rectangle::_Shape>(rectangle.m_size.s, rectangle.m_size.t);
    }, rectangle.id());

    // Draw it
    _Shape::s_shader()
        .use()
        .set("offset", rectangle.m_pos.x,   rectangle.m_pos.y,   rectangle.m_pos.z)
        .set("color",  rectangle.m_color.r, rectangle.m_color.g, rectangle.m_color.b)
        .set("alpha",  rectangle.m_color.a);

    shape->bind();
    shape->draw();
}


// ---- Rectangle data ----
Rectangle::Rectangle(glm::vec3 pos_, glm::vec2 size_, glm::vec4 color_) :
    m_pos(pos_), m_size(size_), m_color(color_)
{ }

std::string Rectangle::id() const {
    return "Rectangle#" + std::to_string(m_size.x) + "." + std::to_string(m_size.y);
}

// Creating rectangle shape
Rectangle::_Shape::_Shape(float width, float height) : BaseShape() {
    // Create
    _addPoint(-width, height, 0.0f);
    _addPoint(width, -height, 0.0f);
    _addPoint(width, height, 0.0f);
    _addPoint(-width, -height, 0.0f);

    _addAsTriangle(1, 2, 3);
    _addAsTriangle(3, 2, 0);

    // Bind
    _bindArray();
}

void Rectangle::_Shape::draw() {
    glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
}

void Rectangle::_Shape::_setAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

// Private Rectangle Shape Helper - Static
Shader& Rectangle::_Shape::s_shader() {
    static int i = 0;
    static bool s_created = false;
    static Shader s_rectangleShader;

    if (!s_created) {
        s_created = true;
        _createShader();
    }
    return s_rectangleShader;
}

void Rectangle::_Shape::_createShader() {
    s_shader()
        .attachSource(GL_VERTEX_SHADER, ShaderSource{}
            .add_var("in", "vec3", "aPos")
            .add_var("uniform", "vec3", "offset")
            .add_func("void", "main", "", R"_main_(
                gl_Position = vec4(aPos + offset, 1.0);
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

