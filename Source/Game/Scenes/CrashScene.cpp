#include "CrashScene.hpp"

#include <glm/gtx/string_cast.hpp>

// Scene instance
CrashScene::CrashScene() :
    BaseScene()
{
    // Camera
    m_camera.position = glm::vec3(0.0f, 3.8f, +0.5f);
    m_camera.direction = glm::vec3(0.0f, 0.0f, +0.5f);
    m_camera.fieldOfView = 45.0f;
}

void CrashScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    _camera_update();
}

void CrashScene::add(const std::shared_ptr<BaseBody>& body) {
    _baseBodies.push_back(body);
}

void CrashScene::lightning(bool enable) {
    m_lights.clear();
    if (!enable)
        return;

    m_lights.push_back(std::make_unique<Light>(
        glm::vec3(0.0f, 0.0f, 1.5f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
    ));
}

void CrashScene::draw() {
    // Place camera
    _camera_update();

    // Draw shapes
    for (auto& body : _baseBodies) {
        body->draw(m_camera, m_lights);
    }
}

void CrashScene::_camera_update() {
    float aspect = (float)m_width / m_height;

    m_camera.lookAt(glm::vec3(0, 0, 1));
    enable_2d_camera ? m_camera.useOrtho(aspect) : m_camera.usePerspective(aspect);
}