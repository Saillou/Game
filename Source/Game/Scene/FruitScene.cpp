#include "FruitScene.hpp"

#include <algorithm>
#include <random>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <array>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

// Objects
class Field : public SceneObject {
    struct _FaceShape : public BaseShape {
        _FaceShape(const std::array<glm::vec3, 4>& quad) {
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

        void draw() override {
            glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
        }

        void _setAttributes() override {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);
        }
    };

    struct _FieldShape : public BaseShape {
        _FieldShape(float width, float height) {
            _addPoint(-width, +width, -height);
            _addPoint(+width, +width, -height);
            _addPoint(+width, -width, -height);
            _addPoint(-width, -width, -height);

            _addPoint(-width, +width, +height);
            _addPoint(+width, +width, +height);
            _addPoint(+width, -width, +height);
            _addPoint(-width, -width, +height);

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

        void draw() override {
            glDrawElements(GL_LINES, (int)m_indices.size(), GL_UNSIGNED_INT, 0);
        }
        void _setAttributes() override {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);
        }
    };

    Shader m_shaderGeom;
    _FieldShape m_borderBack;

    Shader m_shaderSolid;
    std::vector<std::shared_ptr<_FaceShape>> m_surfaceBack;

public:
    Field() :
        m_borderBack(0.5f, 0.5f),
        m_surfaceBack() 
    {
        const glm::vec3 
            A(-0.5f, +0.5f, -0.5f),
            B(+0.5f, +0.5f, -0.5f),
            C(+0.5f, -0.5f, -0.5f),
            D(-0.5f, -0.5f, -0.5f),
            E(-0.5f, +0.5f, +0.5f),
            F(+0.5f, +0.5f, +0.5f),
            G(+0.5f, -0.5f, +0.5f),
            H(-0.5f, -0.5f, +0.5f);

        // Create surfaces
        m_surfaceBack.push_back(std::make_shared<_FaceShape>(std::array<glm::vec3, 4> {A, B, C, D}));
        m_surfaceBack.push_back(std::make_shared<_FaceShape>(std::array<glm::vec3, 4> {B, C, G, F}));
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

    void draw(const Camera& camera, float x, float y, float z = 0.0f) {
        m_shaderGeom
            .use()
            .set("offset", x, y, z)
            .set("color", 1.0f, 0.9f, 0.8f)
            .set("alpha", 1.0f)
            .set("Projection", camera.projection)
            .set("Modelview", camera.modelview);

        m_borderBack.bind();
        m_borderBack.draw();

        m_shaderSolid
            .use()
            .set("offset", x, y, z)
            .set("color", 0.2f, 0.9f, 0.8f)
            .set("alpha", 0.2f)
            .set("Projection", camera.projection)
            .set("Modelview", camera.modelview);

        for (auto& surface : m_surfaceBack) {
            surface->bind();
            surface->draw();
        }
    }
};

// Scene instance
FruitScene::FruitScene() :
    BaseScene()
{
    // Shapes
    m_shapes["Field"] = std::make_shared<Field>();

    // Camera
    m_camera.projection = glm::perspective(glm::radians<float>(25.0f), 1400.0f / 800.0f, 0.1f, 100.0f);
    m_camera.modelview  = glm::lookAt(glm::vec3(1.0f, 3.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void FruitScene::resize(int width, int height) {
    // ..
}

void FruitScene::draw() {
    // Draw objects
    m_shapes["Field"]
        ->as<Field>()
        ->draw(m_camera, 0.0f, 0.0f);

    // Draw texts
    TextEngine::Write("Fruits", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}
