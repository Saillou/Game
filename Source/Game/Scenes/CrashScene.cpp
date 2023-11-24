#include "CrashScene.hpp"

#include <glm/gtx/string_cast.hpp>

// Scene instance
CrashScene::CrashScene() :
    BaseScene()
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, 3.8f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0f, 0.0f);
    m_camera.fieldOfView = 45.0f;

}

void CrashScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

}

void CrashScene::draw() {

    // Draw texts
    TextEngine::Write("CrashScene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}
