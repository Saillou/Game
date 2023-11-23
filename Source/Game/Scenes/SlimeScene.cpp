#include "SlimeScene.hpp"

// Scene instance
SlimeScene::SlimeScene() :
    BaseScene()
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, 3.8f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0f, 0.0f);
    m_camera.fieldOfView = 45.0f;
}

void SlimeScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    _camera_update();
}

void SlimeScene::add(const std::shared_ptr<BaseBody>& body) {
    _baseBodies.push_back(body);
}

void SlimeScene::draw() {
    // Draw shapes
    for (auto& body : _baseBodies) {
        body->draw(m_camera, m_lights);
    }

    // Draw texts
    TextEngine::Write("SlimeScene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void SlimeScene::_camera_update() {
    float aspect = (float)m_width / m_height;

    m_camera.lookAt(glm::vec3(0, 0, 1));
    m_camera.useOrtho(aspect);
    //m_camera.usePerspective(aspect);
}