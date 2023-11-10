#include "FruitScene.hpp"

#include <algorithm>
#include <random>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../../Utils/Caster.hpp"

#include <glm/gtc/matrix_transform.hpp>

// Objects
class Field : public SceneObject {
    struct _FieldShape : public BaseShape {
        _FieldShape(float width, float height) {
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

        }
        void _setAttributes() override {

        }
    };

public:
    Field() : 
        SceneObject(std::make_unique<_FieldShape>(0.15f, 0.15f)) 
    {
        m_shader
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

    void draw(float x, float y, float z = 0.0f) {
        m_shader
            .use()
            .set("offset", x, y, z)
            .set("color",  1.0f, 0.9f, 0.8f)
            .set("alpha",  1.0f);

        SceneObject::draw();
    }
};

class Fruit : public SceneObject {
    struct _FruitShape : public BaseShape {
        _FruitShape() {

        }

        void draw() override {

        }
        void _setAttributes() override {

        }
    };

public:
    Fruit() : SceneObject(std::make_unique<_FruitShape>()) {
        m_shader
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
};


// Scene instance
FruitScene::FruitScene() :
    BaseScene()
{
    m_shapes["Field"] = std::make_unique<Field>();
    m_shapes["Fruit"] = std::make_unique<Fruit>();
}

void FruitScene::resize(int width, int height) {
    // ..
}

void FruitScene::draw() {
    // Draw objects
    dynamic_unique_ptr_cast<Field, SceneObject>(std::move(m_shapes["Field"]));

    // Draw texts
    TextEngine::Write("Fruits", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}
