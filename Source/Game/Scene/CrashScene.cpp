#include "CrashScene.hpp"

#include <sstream>
#include <vector>
#include <unordered_map>
#include <utility>

#include "Objects/Facette.hpp"
#include "Objects/Sphere.hpp"

// Scene instance
CrashScene::CrashScene() : BaseScene() {
    // ..
}

void CrashScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    m_camera.projection = glm::perspective(glm::radians<float>(25.0f), (float)width / height, 0.1f, 100.0f);
    m_camera.modelview  = glm::lookAt(glm::vec3(1.0f, 3.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void CrashScene::draw() {

    // Draw texts
    TextEngine::Write("Crash scene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}
