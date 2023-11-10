#include "Field.hpp"

// -- Shapes --
// - Face
Field::_FaceShape::_FaceShape(const std::array<glm::vec3, 4>& quad) {
    _addPoint(quad[0].x, quad[0].y, quad[0].z);
    _addPoint(quad[1].x, quad[1].y, quad[1].z);
    _addPoint(quad[2].x, quad[2].y, quad[2].z);
    _addPoint(quad[3].x, quad[3].y, quad[3].z);

    auto __face = [=](int a, int b, int c, int d) {
        _addAsTriangle(c, b, d);
        _addAsTriangle(d, b, a);
    };

    __face(0, 1, 2, 3);

    // Bind
    _bindArray();
}

void Field::_FaceShape::draw() {
    glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
}

void Field::_FaceShape::_setAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

// - Border
Field::_FieldShape::_FieldShape(float width, float depth, float height) {
    _addPoint(-width, +depth, -height);
    _addPoint(+width, +depth, -height);
    _addPoint(+width, -depth, -height);
    _addPoint(-width, -depth, -height);

    _addPoint(-width, +depth, +height);
    _addPoint(+width, +depth, +height);
    _addPoint(+width, -depth, +height);
    _addPoint(-width, -depth, +height);

    _addAsLine(0, 1);
    _addAsLine(1, 2);
    _addAsLine(2, 3);
    _addAsLine(3, 0);

    _addAsLine(0, 4);
    _addAsLine(1, 5);
    _addAsLine(2, 6);
    _addAsLine(3, 7);

    _addAsLine(5, 6);
    _addAsLine(6, 7);
    _addAsLine(7, 4);


    // Bind
    _bindArray();
}

void Field::_FieldShape::draw() {
    glDrawElements(GL_LINES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
}
void Field::_FieldShape::_setAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}



// Shader and param
Field::Field(float width, float depth, float height)
{
    m_borderBack = std::make_shared<_FieldShape>(width, depth, height);

    const glm::vec3
        A(-width, +depth, -height),
        B(+width, +depth, -height),
        C(+width, -depth, -height),
        D(-width, -depth, -height),
        E(-width, +depth, +height),
        F(+width, +depth, +height),
        G(+width, -depth, +height),
        H(-width, -depth, +height);

    // Create surfaces
    m_surfaceBack.push_back(std::make_shared<_FaceShape>(std::array<glm::vec3, 4> {A, B, C, D}));
    m_surfaceBack.push_back(std::make_shared<_FaceShape>(std::array<glm::vec3, 4> {C, B, F, G}));
    m_surfaceBack.push_back(std::make_shared<_FaceShape>(std::array<glm::vec3, 4> {A, D, H, E}));
    m_surfaceBack.push_back(std::make_shared<_FaceShape>(std::array<glm::vec3, 4> {C, G, H, D}));
    m_surfaceBack.push_back(std::make_shared<_FaceShape>(std::array<glm::vec3, 4> {B, F, E, A}));

    // Create shaders
    m_shaderGeom
        .attachSource(GL_VERTEX_SHADER, ShaderSource{}
            .add_var("in", "vec3", "aPos")
            .add_var("uniform", "vec3", "offset")
            .add_var("uniform", "mat4", "Projection")
            .add_var("uniform", "mat4", "Modelview")
            .add_func("void", "main", "", R"_main_(
                gl_Position = Projection * Modelview * vec4(aPos + offset, 1.0);
            )_main_").str()
        )
        .attachSource(GL_GEOMETRY_SHADER, ShaderSource{}
            .add_var("in", "layout", "(lines)")
            .add_var("out", "layout", "(line_strip, max_vertices = 6)")
            .add_func("void", "main", "", R"_main_(
                gl_Position     = gl_in[0].gl_Position; EmitVertex();
                gl_Position     = gl_in[1].gl_Position; EmitVertex(); 
                EndPrimitive();
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

    m_shaderSolid
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

void Field::draw(const Camera& camera, const glm::vec3& pos) {
    m_shaderGeom
        .use()
        .set("offset", pos.x, pos.y, pos.z)
        .set("color", 1.0f, 0.9f, 0.8f)
        .set("alpha", 0.5f)
        .set("Projection", camera.projection)
        .set("Modelview", camera.modelview);

    m_borderBack->bind();
    m_borderBack->draw();

    m_shaderSolid
        .use()
        .set("offset", pos.x, pos.y, pos.z)
        .set("color", 0.2f, 0.9f, 0.8f)
        .set("alpha", 0.05f)
        .set("Projection", camera.projection)
        .set("Modelview", camera.modelview);

    for (auto& surface : m_surfaceBack) {
        surface->bind();
        surface->draw();
    }
}