#include "Box.hpp"

#include <iostream>
#include <sstream>
#include <glm/gtx/string_cast.hpp>

using v3 = glm::vec3;

// - Shape
struct BoxShape : public BaseShape 
{
    BoxShape(const glm::vec3& dims) 
    {
        const glm::mat3 world(1.0f); // identity

        const v3 u = dims[0] * world[0];
        const v3 v = dims[1] * world[1];
        const v3 w = dims[2] * world[2];

        // Vertices positions
        const v3 A = -u +v -w;
        const v3 B = +u +v -w;
        const v3 C = +u -v -w;
        const v3 D = -u -v -w;

        const v3 E = -u +v +w;
        const v3 F = +u +v +w;
        const v3 G = +u -v +w;
        const v3 H = -u -v +w;

        _create_quad(D, C, B, A, -w);
        _create_quad(H, G, F, E, +w);

        _create_quad(E, A, D, H, -u);
        _create_quad(F, B, C, G, +u);

        _create_quad(D, C, G, H, -v);
        _create_quad(A, B, F, E, +v);

        // Bind
        _bindArray();
    }

    void draw() override {
        glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
    }

private:
    // - Drawing
    void BoxShape::_create_quad(const v3& P0, const v3& P1, const v3& P2, const v3& P3, const v3& n) {
        int i0 = _addPoint(P0, n);
        int i1 = _addPoint(P1, n);
        int i2 = _addPoint(P2, n);
        int i3 = _addPoint(P3, n);

        _addAsTriangle(i0, i1, i2);
        _addAsTriangle(i2, i3, i0);
    };

};

// - Constructor
Box::Box(const glm::vec3& dims) :
    m_shape(std::make_shared<BoxShape>(dims))
{
    // ...
}

void Box::bind() {
    ((BoxShape*)m_shape.get())->bind();
}

void Box::draw(const Camera& camera, const glm::vec3& position, const glm::vec3& orientation, const std::vector<std::unique_ptr<Light>>& lights) {
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

        bind();
        ((BoxShape*)m_shape.get())->draw();
    }
}
