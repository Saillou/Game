#include "Ellipse.hpp"

#include <sstream>
#include <vector>
#include <utility>
#include <unordered_map>

// -------- Public Ellipse Helper - Static --------
void Ellipse::Draw(glm::vec3 pos, glm::vec2 size, glm::vec2 angles, glm::vec4 color) {
    // Get the needed shape
    Ellipse ellipse(pos, size, color);
    const auto& shape = _Get_Or_Create(ellipse);

    // Draw it
    _Shape::s_shader()
        .use()
        .set("offset", ellipse.m_pos.x,   ellipse.m_pos.y,   ellipse.m_pos.z)
        .set("color",  ellipse.m_color.r, ellipse.m_color.g, ellipse.m_color.b)
        .set("alpha",  ellipse.m_color.a);

    // Angle limit
    const auto N_pts = shape->m_indices.size() * std::abs(angles.s - angles.t) / (2.0f*glm::pi<float>());
    shape->bind();
    shape->draw(0, (int)N_pts + 3);
}


// ---- Ellipse data ----
Ellipse::Ellipse(glm::vec3 pos_, glm::vec2 size_, glm::vec4 color_) :
    m_pos(pos_), m_size(size_), m_color(color_)
{ }

std::string Ellipse::_id() const {
    return std::to_string(m_size.x) + "." + std::to_string(m_size.y);
}

// Creating and caching shapes
std::unique_ptr<Ellipse::_Shape>& Ellipse::_Get_Or_Create(const Ellipse& ellipse) {
    // Cache all ellipses' shape ever created (may need to clean it up with LFU's cache)
    static std::unordered_map<std::string, std::unique_ptr<_Shape>> s_shapes;
    const auto shape_key = ellipse._id();

    const auto it_shape = s_shapes.find(shape_key);
    if (it_shape == s_shapes.cend())
        s_shapes[shape_key] = std::make_unique<Ellipse::_Shape>(ellipse.m_size.s, ellipse.m_size.t);

    return s_shapes.at(shape_key);
}

// Creating ellipse shape
Ellipse::_Shape::_Shape(float width, float height) : BaseShape() {
    constexpr float dtheta = glm::pi<float>() / 20.0f;
    constexpr int N_POINTS = (int)(2.0f * glm::pi<float>() / dtheta);

    // start
    float xi = width / 2;
    float yi = 0;

    _addPoint(0, 0, 0);    // center
    _addPoint(xi, yi, 0);  // first point

    // then, put points on the border of the ellipse
    for (int i = 0; i <= N_POINTS; i++) {
        xi = width / 2 * glm::cos(dtheta * i);
        yi = height / 2 * glm::sin(dtheta * i);
        _addPoint(xi, yi, 0.0f);
        _addAsTriangle(0, i+1, i+2); // all triangles start from the center
    }

    // Bind
    _bindArray();
}

void Ellipse::_Shape::draw() {
    glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Ellipse::_Shape::draw(int ptStart, int nPoints) {
    glDrawElements(GL_TRIANGLES, nPoints, GL_UNSIGNED_INT, nullptr);
}

void Ellipse::_Shape::_setAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

// Private Ellipse Shape Helper - Static
Shader& Ellipse::_Shape::s_shader() {
    static int i = 0;
    static bool s_created = false;
    static Shader s_ellipseShader;

    if (!s_created) {
        s_created = true;
        _createShader();
    }
    return s_ellipseShader;
}

void Ellipse::_Shape::_createShader() {
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

