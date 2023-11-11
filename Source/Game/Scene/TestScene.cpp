#include "TestScene.hpp"

#include "Objects/Facette.hpp"
#include "Objects/Field.hpp"
#include "Objects/Fruit.hpp"


// Scene instance
TestScene::TestScene() :
    BaseScene()
{
    // Data
    const float 
        width(0.50f), 
        depth(0.25f), 
        height(0.6f);

    const glm::vec3
        A(-width, +depth, -height),
        B(+width, +depth, -height),
        C(+width, -depth, -height),
        D(-width, -depth, -height),
        E(-width, +depth, +height),
        F(+width, +depth, +height),
        G(+width, -depth, +height),
        H(-width, -depth, +height);

    const glm::vec4 
        color_solid( 1.0f, 0.0f, 0.0f, 0.2f),
        color_border(0.0f, 1.0f, 0.0f, 1.0f),
        color_point( 1.0f, 1.0f, 1.0f, 1.0f);

    // Create objects
    m_shapes["Ground"] = std::make_shared<Facette>(Facette::Quad{ A,B,C,D });

    // Cook style
    m_shapes["Ground"]
        ->as<Facette>()
        ->addRecipe(Facette::CookType::Solid,  color_solid)
        ->addRecipe(Facette::CookType::Point,  color_point)
        ->addRecipe(Facette::CookType::Border, color_border)
    ;
}

void TestScene::resize(int width, int height) {
    // Camera
    m_camera.modelview = glm::lookAt(
        glm::vec3(-0.25f, 3.0f, 0.75f), 
        glm::vec3(-0.30f, 0.0f, 0.00f), 
        glm::vec3(+0.00f, 0.0f, 1.00f)
    );

    m_camera.projection = glm::perspective(
        glm::radians<float>(30.0f), 
        (float)width / height,
        0.1f, 100.0f
    );
}

void TestScene::draw() {
    // Draw objects
    m_shapes["Ground"]
        ->as<Facette>()
        ->draw(m_camera, glm::vec3(0.0f, -1.0f, 0.0f));

    // Draw texts
    TextEngine::Write("Test Scene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}
