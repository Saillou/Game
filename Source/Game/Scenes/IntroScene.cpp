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

    // Objects
    m_planet = std::make_unique<Sphere>(0.05f);
    m_planet->addRecipe(Cookable::CookType::Solid, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-30.0f, +30.0);

    m_universe.resize(1000);
    std::generate(m_universe.begin(), m_universe.end(), [&]() -> glm::vec3 {
        return glm::vec3(
            distribution(generator), 
            distribution(generator), 
            distribution(generator)
        );
    });
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

    // Draw shapes
    for (const auto& planet_pos : m_universe) {
        m_planet->draw(m_camera, planet_pos, {}, m_lights);
    }
}

void IntroScene::_update_camera() {
    float aspect = (float)m_width / m_height;

    m_camera.lookAt(glm::vec3(0, 0, 1));
    m_camera.usePerspective(aspect);
}