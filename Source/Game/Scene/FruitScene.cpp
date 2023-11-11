#include "FruitScene.hpp"

#include "Objects/Facette.hpp"
#include "Objects/Sphere.hpp"


// Scene instance
FruitScene::FruitScene() :
    BaseScene()
{
    // Data
    const glm::vec3 pOrigin(0.f, 0.f, 0.f);

    const glm::vec3 uDirect(1.f, 0.f, 0.f);
    const glm::vec3 uNormal(0.f, 1.f, 0.f);
    const glm::vec3 uHeight(0.f, 0.f, 1.f);

    const glm::vec4 borderColor(1.0f, 1.0f, 1.0f, 1.0f);
    const glm::vec4 groundColor(1.0f, 0.7f, 0.3f, 1.0f);
    const glm::vec4 bucketColor(0.3f, 0.7f, 1.0f, 1.0f);

    const float bucketWidth  = 0.50f;
    const float bucketHeight = 0.50f;
    const float bucketDepth  = 0.10f;

    // Shapes
    m_shapes["Ground"] = std::make_shared<Facette>(pOrigin - 0.01f*uHeight, 10.0f*uDirect, 10.0f*uNormal);

    m_shapes["bucketWest"] = std::make_shared<Facette>(pOrigin - bucketWidth*uDirect + bucketHeight*uHeight, bucketDepth*uNormal, bucketHeight*uHeight);
    m_shapes["bucketEast"] = std::make_shared<Facette>(pOrigin + bucketWidth*uDirect + bucketHeight*uHeight, bucketDepth*uNormal, bucketHeight*uHeight);
    m_shapes["bucketBack"] = std::make_shared<Facette>(pOrigin,  bucketWidth*uDirect,  bucketDepth*uNormal);

    // Style
    m_shapes["Ground"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, groundColor);

    m_shapes["bucketBack"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, bucketColor)
        ->addRecipe(Facette::CookType::Border, borderColor);

    m_shapes["bucketWest"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, bucketColor)
        ->addRecipe(Facette::CookType::Border, borderColor);

    m_shapes["bucketEast"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, bucketColor)
        ->addRecipe(Facette::CookType::Border, borderColor);
}

void FruitScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    m_camera.modelview  = glm::lookAt(glm::vec3(0.0f, 3.0f, 0.5F), glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_camera.projection = glm::perspective(glm::radians<float>(30.0f), (float)width / height, 0.1f, 100.0f);
}

void FruitScene::draw() {
    // Draw objects
    m_shapes["Ground"]->as<Facette>()->draw(m_camera);

    m_shapes["bucketBack"]->as<Facette>()->draw(m_camera);
    m_shapes["bucketWest"]->as<Facette>()->draw(m_camera);
    m_shapes["bucketEast"]->as<Facette>()->draw(m_camera);

    // Draw texts
    int score = 0;
    TextEngine::Write("Score: " + std::to_string(score), 10.0f, m_height - 30.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
    TextEngine::Write("Fruits Scene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}
