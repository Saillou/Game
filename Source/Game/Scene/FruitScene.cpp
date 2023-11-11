#include "FruitScene.hpp"

#include "Objects/Facette.hpp"
#include "Objects/Sphere.hpp"


// Scene instance
FruitScene::FruitScene() :
    BaseScene()
{
    // Shapes
    //m_shapes["Fruit"] = std::make_shared<Fruit>(0.15f);
    //m_shapes["Field"] = std::make_shared<Field>(0.6f, 0.25f, 0.5f);

    // Camera
    m_camera.modelview  = glm::lookAt(glm::vec3(-0.25f, 3.0f, 0.75F), glm::vec3(-0.3f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void FruitScene::resize(int width, int height) {
    m_camera.projection = glm::perspective(glm::radians<float>(30.0f), (float)width / height, 0.1f, 100.0f);
}

void FruitScene::draw() {
    // Draw objects
    //m_shapes["Fruit"]->as<Fruit>()->draw(m_camera, glm::vec3(0.0f, -1.0f, 0.0f));
    //m_shapes["Fruit"]->as<Fruit>()->draw(m_camera, glm::vec3(0.0f, -1.0f, 0.5f));

    //m_shapes["Field"]->as<Field>()->draw(m_camera, glm::vec3(0.0f, 0.0f, 0.0f));

    // Draw texts
    TextEngine::Write("Fruits Scene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}
