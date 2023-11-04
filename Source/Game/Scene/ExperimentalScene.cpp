#include "ExperimentalScene.hpp"

#include <sstream>
#include <vector>
#include <glm/glm.hpp>

ExperimentalScene::ExperimentalScene() : BaseScene() {
    // Create shaders
    m_shader.attachSource(GL_VERTEX_SHADER, ShaderSource{}
        .add_var("in", "vec3", "aPos")
        .add_func("void", "main", "", R"_main_(
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    )_main_").str());

    m_shader.attachSource(GL_FRAGMENT_SHADER, ShaderSource{}
        .add_var("out", "vec4", "FragColor")
        .add_func("void", "main", "", R"_main_(
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    )_main_").str());

    m_shader.link();

    // Create shapes
    struct RectangleShape : public Shape {
        RectangleShape(float width, float height) : Shape() {
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

        void draw() override {
            glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
        }

        void _setAttributes() override {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);
        }
    };

    m_shapes["Shape_1"] = std::make_unique<RectangleShape>(0.5f, 0.5f);
}

void ExperimentalScene::resize(int width, int height) {
    // ..
}

void ExperimentalScene::draw() {
    // Background
    glClearColor(0.05f, 0.05f, 0.06f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw shapes
    m_shader.use();
    m_shapes["Shape_1"]->bind();
    m_shapes["Shape_1"]->draw();
    // ..
}
