#include "Sphere.hpp"

// - Helpers -
static void s_set_shader_common(UShader&);
static void s_set_shader_solid(UShader&);
static void s_set_shader_border(UShader&);
static void s_set_shader_point(UShader&);

// - Shape
struct SphereShape : public BaseShape {
    SphereShape(const glm::vec3& center, float radius) 
    {
        const unsigned int X_SEGMENTS = 16;
        const unsigned int Y_SEGMENTS = 16;

        for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
            for (unsigned int y = 0; y <= Y_SEGMENTS; ++y) {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                
                _addPoint(
                    center.x + radius * std::cos(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>()),
                    center.y + radius * std::cos(ySegment * 1.0f * glm::pi<float>()),
                    center.z + radius * std::sin(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>())
                );
            }
        }

        for (unsigned int y = 0; y < Y_SEGMENTS; ++y) {
            if (y%2 == 0) {
                for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
                    m_indices.push_back(y * (X_SEGMENTS + 1) + x);
                    m_indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                }
            }
            else {
                for (int x = X_SEGMENTS; x >= 0; --x) {
                    m_indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                    m_indices.push_back(y * (X_SEGMENTS + 1) + x);
                }
            }
        }

        // Bind
        _bindArray();
    }

    void draw() override {
        glDrawElements(GL_TRIANGLE_STRIP, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
    }
    void _setAttributes() override {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
    }
};

// - Constructor
Sphere::Sphere(const glm::vec3& center, float radius) :
    m_shape(std::make_shared<SphereShape>(center, radius))
{
}

Sphere* Sphere::addRecipe(const CookType& type, const glm::vec4& color) {
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

void Sphere::draw(const Camera& camera, const glm::vec3& position, const glm::vec3& orientation) {
    glm::mat4 model(1.0f);
    model = glm::rotate(model, orientation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, orientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, orientation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, position);

    for (auto& recipe: m_shaders) {
        recipe->
            use().
            set("Model",        model).
            set("View",         camera.modelview).
            set("Projection",   camera.projection);

        ((SphereShape*)m_shape.get())->bind();
        ((SphereShape*)m_shape.get())->draw();
    }
}

// - Shader
void s_set_shader_common(UShader& shader) {
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