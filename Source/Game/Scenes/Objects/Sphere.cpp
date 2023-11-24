#include "Sphere.hpp"

// - Shape
struct SphereShape : public BaseShape {
    SphereShape(float radius) 
    {
        const unsigned int X_SEGMENTS = 32;
        const unsigned int Y_SEGMENTS = 32;

        for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
            for (unsigned int y = 0; y <= Y_SEGMENTS; ++y) {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                
                _addPoint(
                    radius * std::cos(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>()),
                    radius * std::cos(ySegment * 1.0f * glm::pi<float>()),
                    radius * std::sin(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>()),

                    radius * std::cos(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>()),
                    radius * std::cos(ySegment * 1.0f * glm::pi<float>()),
                    radius * std::sin(xSegment * 2.0f * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>())
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
};

// - Constructor
Sphere::Sphere(const glm::vec3& center, float radius) :
    m_shape(std::make_shared<SphereShape>(radius))
{
    // ..
}

void Sphere::draw(const Camera& camera, const glm::vec3& position, const glm::vec3& orientation, const std::vector<std::unique_ptr<Light>>& lights) {
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
            set("Projection",   camera.projection).
            set("CameraPos",    camera.position).
            set("LightPos",     glm::vec3(0, 0, 0)).
            set("LightColor",   glm::vec4(0, 0, 0, 0));

        if(!lights.empty()) {
            recipe->
                set("LightPos",   lights[0]->position).
                set("LightColor", lights[0]->color);
        }

        ((SphereShape*)m_shape.get())->bind();
        ((SphereShape*)m_shape.get())->draw();
    }
}

// - Shaders
void Sphere::_set_shader_border(UShader& shader) {
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

void Sphere::_set_shader_point(UShader& shader) {
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
