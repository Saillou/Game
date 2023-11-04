#include "Rectangle.hpp"

#include <sstream>
#include <vector>
#include <utility>
#include <unordered_map>

// -------- Public Rectangle Helper - Static --------
void Rectangle::Draw(glm::vec3 pos, glm::vec2 size, glm::vec4 color) {
    // Get the needed shape
    Rectangle rectangle(pos, size, color);
    const auto& shape = _Get_Or_Create(rectangle);

    // Draw it
    _Shape::s_shader()
        .use()
        .set("offset", rectangle.m_pos.x, rectangle.m_pos.y, rectangle.m_pos.z)
        .set("color",  rectangle.m_color.r, rectangle.m_color.g, rectangle.m_color.b)
        .set("alpha",  rectangle.m_color.a);

    shape->bind();
    shape->draw();
}


// ---- Rectangle data ----
Rectangle::Rectangle(glm::vec3 pos_, glm::vec2 size_, glm::vec4 color_) :
    m_pos(pos_), m_size(size_), m_color(color_)
{ }

std::string Rectangle::_id() const {
    return std::to_string(m_size.x) + "." + std::to_string(m_size.y);
}

// Creating and caching shapes
std::unique_ptr<BaseShape>& Rectangle::_Get_Or_Create(const Rectangle& rectangle) {
    // Cache all rectangles' shape ever created (may need to clean it up with LFU's cache)
    static std::unordered_map<std::string, std::unique_ptr<BaseShape>> s_shapes;
    const auto shape_key = rectangle._id();

    const auto it_shape = s_shapes.find(shape_key);
    if (it_shape == s_shapes.cend())
        s_shapes[shape_key] = std::make_unique<Rectangle::_Shape>(rectangle.m_size.s, rectangle.m_size.t);

    return s_shapes.at(shape_key);
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

