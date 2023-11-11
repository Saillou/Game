#include "Parallelepiped.hpp"

// - Helpers -
static void s_set_shader_common(UShader&);
static void s_set_shader_solid(UShader&);
static void s_set_shader_border(UShader&);
static void s_set_shader_point(UShader&);

// - Shape
struct ParallelepipedShape : public BaseShape {
    ParallelepipedShape(const glm::vec3& center, const glm::vec3& u, const glm::vec3& n, const glm::vec3& w) {
        _addPoint(center + (-u + n) - w);
        _addPoint(center + (+u + n) - w);
        _addPoint(center + (+u - n) - w);
        _addPoint(center + (-u - n) - w);

        _addPoint(center + (-u + n) + w);
        _addPoint(center + (+u + n) + w);
        _addPoint(center + (+u - n) + w);
        _addPoint(center + (-u - n) + w);

        auto __face = [=](int a, int b, int c, int d) {
            _addAsTriangle(a, b, c);
            _addAsTriangle(c, d, a);
        };

        __face(0, 1, 2, 3);
        __face(0, 1, 5, 4);
        __face(1, 2, 6, 5);
        __face(2, 3, 7, 6);
        __face(3, 0, 4, 7);
        __face(4, 5, 6, 7);

        // Bind
        _bindArray();
    }

    void draw() override {
        glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
    }

private:
    void _setAttributes() override {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
    }
};

// - Constructor
Parallelepiped::Parallelepiped(const glm::vec3& center, const glm::vec3& u, const glm::vec3& n, const glm::vec3& w) :
    m_shape(std::make_shared<ParallelepipedShape>(center, u, n, w))
{
}

Parallelepiped* Parallelepiped::addRecipe(const CookType& type, const glm::vec4& color) {
    m_shaders.push_back(std::make_unique<Shader>());
    UShader& recipe = m_shaders.back();

    switch (type) {
    case CookType::Solid:  
        s_set_shader_solid(recipe);
        break;

    case CookType::Border: 
        s_set_shader_border(recipe);
        break;

    case CookType::Point:
        s_set_shader_point(recipe);
        break;

    default:
        return this;
    }

    // Set uniforms
    recipe->use().set("color", color);

    // Allow chained calls
    return this;
}

void Parallelepiped::draw(const Camera& camera, const glm::vec3& position) {
    for (auto& recipe: m_shaders) {
        recipe->
            use().
            set("offset",       position).
            set("Projection",   camera.projection).
            set("Modelview",    camera.modelview);

        ((ParallelepipedShape*)m_shape.get())->bind();
        ((ParallelepipedShape*)m_shape.get())->draw();
    }
}

// - Shader
void s_set_shader_common(UShader& shader) {
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

void s_set_shader_solid(UShader& shader) {
    s_set_shader_common(shader);

    shader->
        link();
}

void s_set_shader_border(UShader& shader) {
    s_set_shader_common(shader);

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

void s_set_shader_point(UShader& shader) {
    s_set_shader_common(shader);

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