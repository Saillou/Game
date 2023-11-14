#include "Facette.hpp"

// - Shape
struct FacetteShape : public BaseShape {
    FacetteShape(const Facette::Quad& points) {
        _addPoint(points[0]);
        _addPoint(points[1]);
        _addPoint(points[2]);
        _addPoint(points[3]);

        _createVertices();
    }

    FacetteShape(const glm::vec3& center, const glm::vec3& u, const glm::vec3& n) {
        _addPoint(center + (-u + n));
        _addPoint(center + (+u + n));
        _addPoint(center + (+u - n));
        _addPoint(center + (-u - n));

        _createVertices();
    }

    void draw() override {
        glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
    }

private:
    void _setAttributes() override {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
    }

    void _createVertices() {
        auto __face = [=](int a, int b, int c, int d) {
            _addAsTriangle(a, b, c);
            _addAsTriangle(c, d, a);
        };

        __face(0, 1, 2, 3);

        // Bind
        _bindArray();
    }
};

// - Constructor
Facette::Facette(const Quad& points) :
    m_shape(std::make_shared<FacetteShape>(points))
{
}

Facette::Facette(const glm::vec3& center, const glm::vec3& u, const glm::vec3& n) :
    m_shape(std::make_shared<FacetteShape>(center, u, n))
{
}

void Facette::draw(const Camera& camera, const glm::vec3& position) {
    for (auto& recipe: m_shaders) {
        recipe->
            use().
            set("offset",       position).
            set("Projection",   camera.projection).
            set("Modelview",    camera.modelview);

        ((FacetteShape*)m_shape.get())->bind();
        ((FacetteShape*)m_shape.get())->draw();
    }
}

// - Shader
void Facette::_set_shader_common(UShader& shader) {
    shader->
        attachSource(GL_VERTEX_SHADER, ShaderSource{}
            .add_var("in", "vec3", "aPos")
            .add_var("uniform", "vec3", "offset")
            .add_var("uniform", "mat4", "Projection")
            .add_var("uniform", "mat4", "Modelview")
            .add_func("void", "main", "", R"_main_(
                gl_Position = Projection * Modelview * vec4(aPos + offset, 1.0);
            )_main_").str()
        ).
        attachSource(GL_FRAGMENT_SHADER, ShaderSource{}
            .add_var("uniform", "vec4", "color")
            .add_var("out", "vec4", "FragColor")
            .add_func("void", "main", "", R"_main_(
                FragColor = color;
            )_main_").str()
        );
}

void Facette::_set_shader_solid(UShader& shader) {
    Facette::_set_shader_common(shader);
    shader->link();
}

void Facette::_set_shader_border(UShader& shader) {
    _set_shader_common(shader);

    shader->
        attachSource(GL_GEOMETRY_SHADER, ShaderSource{}
            .add_var("in", "layout", "(triangles)")
            .add_var("out", "layout", "(line_strip, max_vertices = 4)")
            .add_func("void", "main", "", R"_main_(
                    gl_Position     = gl_in[1].gl_Position; EmitVertex();
                    gl_Position     = gl_in[2].gl_Position; EmitVertex(); 
                    EndPrimitive();

                    gl_Position     = gl_in[0].gl_Position; EmitVertex();
                    gl_Position     = gl_in[1].gl_Position; EmitVertex(); 
                    EndPrimitive();
                )_main_").str()
        ).link();
}

void Facette::_set_shader_point(UShader& shader) {
    _set_shader_common(shader);

    shader->
        attachSource(GL_GEOMETRY_SHADER, ShaderSource{}
            .add_var("in", "layout", "(triangles)")
            .add_var("out", "layout", "(points, max_vertices = 2)")
            .add_func("void", "main", "", R"_main_(
                    gl_Position     = gl_in[0].gl_Position; EmitVertex();
                    EndPrimitive();

                    gl_Position     = gl_in[1].gl_Position; EmitVertex(); 
                    EndPrimitive();
                )_main_").str()
        ).link();
}