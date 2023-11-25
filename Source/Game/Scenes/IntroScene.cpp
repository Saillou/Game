#include "IntroScene.hpp"

#include <algorithm>
#include <ctime>
#include <random>

#include <glm/gtx/string_cast.hpp>

// Scene instance
IntroScene::IntroScene() :
    BaseScene()
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, 3.8f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0f, 0.0f);
    m_camera.fieldOfView = 45.0f;

    // - Generate batch of planets
    // Shape
    m_planet = std::make_unique<Sphere>(0.25f);
    m_planet->addRecipe(Cookable::CookType::Batch, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    // Random position
    std::default_random_engine gen;
    std::uniform_real_distribution<float> dstr(-100.0f, +100.0f);

    m_planets_pose.resize(10000);
    std::generate(m_planets_pose.begin(), m_planets_pose.end(), [&]() -> glm::mat4 {
        return glm::translate(glm::mat4(1.0f), glm::vec3(dstr(gen), dstr(gen), dstr(gen)));
    });

    // Create batch
    Buffer planets_buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    planets_buffer.bindData(m_planets_pose);

    m_planet->bind();

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    m_planet->unbind();
}

void IntroScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    _update_camera();
}

void IntroScene::draw() {
    // Camera
    _update_camera();

    // Draw universe
    m_planet->drawBatch((int)m_planets_pose.size(), m_camera, m_lights);
}

void IntroScene::_update_camera() {
    float aspect = (float)m_width / m_height;

    m_camera.lookAt(glm::vec3(0, 0, 1));
    m_camera.usePerspective(aspect);
}