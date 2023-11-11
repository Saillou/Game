#include "SlimeScene.hpp"

#include "Objects/Facette.hpp"
#include "Objects/Sphere.hpp"

// Scene instance
SlimeScene::SlimeScene() : BaseScene() {
    // ..
}

void SlimeScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    m_camera.modelview = glm::lookAt(glm::vec3(0.0f, 3.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_camera.projection = glm::perspective(glm::radians<float>(30.0f), (float)width / height, 0.1f, 100.0f);
}

void SlimeScene::draw() {

    // Draw texts
    TextEngine::Write("Slime scene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}
