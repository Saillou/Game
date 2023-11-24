#include "EndingScene.hpp"

#include <glm/gtx/string_cast.hpp>

// Scene instance
EndingScene::EndingScene() :
    BaseScene()
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, 3.8f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0f, 0.0f);
    m_camera.fieldOfView = 45.0f;

}

void EndingScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

}

void EndingScene::draw() {
    // Draw texts
    TextEngine::Write("To my wife,", 10.0f, m_height - 20.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
    TextEngine::Write("without whom this game would have been completed 2 weeks ago.", 50.0f, m_height - 40.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));

    TextEngine::Write("Perspective", m_width * 0.45f, m_height * 0.8f, 0.8f, glm::vec3(1.0f, 1.0f, 1.0f));
    TextEngine::Write("What are the other things hidden from the view?", m_width * 0.375f, m_height * 0.8f - 40.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
}
