#include "Box.hpp"

// - Shape
struct BoxShape : public BaseShape {
    BoxShape(const glm::vec3& dims) {
        const glm::mat3 world(1.0f);
        const glm::vec3 u = dims[0] * world[0];
        const glm::vec3 v = dims[1] * world[1];
        const glm::vec3 w = dims[2] * world[2];

        _addPoint((-u + v) - w);
        _addPoint((+u + v) - w);
        _addPoint((+u - v) - w);
        _addPoint((-u - v) - w);

        _addPoint((-u + v) + w);
        _addPoint((+u + v) + w);
        _addPoint((+u - v) + w);
        _addPoint((-u - v) + w);

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
Box::Box(const glm::vec3& dims) :
    m_shape(std::make_shared<BoxShape>(dims))
{
}

void Box::draw(const Camera& camera, const glm::vec3& position, const glm::vec3& orientation) {
    glm::mat4 model(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, orientation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, orientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, orientation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    for (auto& recipe: m_shaders) {
        recipe->
            use().
            set("Model",        model).
            set("View",         camera.modelview).
            set("Projection",   camera.projection);

        ((BoxShape*)m_shape.get())->bind();
        ((BoxShape*)m_shape.get())->draw();
    }
}

// - Shader
void Box::_set_shader_common(UShader& shader) {
    shader->
        attachSource(GL_VERTEX_SHADER, ShaderSource{}
            .add_var("in", "vec3", "aPos")
            .add_var("uniform", "mat4", "Projection")
            .add_var("uniform", "mat4", "View")
            .add_var("uniform", "mat4", "Model")
            .add_func("void", "main", "", R"_main_(
                gl_Position = Projection * View * Model * vec4(aPos, 1.0);
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

void Box::_set_shader_solid(UShader& shader) {
    _set_shader_common(shader);
    shader->link();
}

void Box::_set_shader_border(UShader& shader) {
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

void Box::_set_shader_point(UShader& shader) {
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