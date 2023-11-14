#include "CrashScene.hpp"

#include "Objects/Parallelepiped.hpp"
#include "Objects/Facette.hpp"
#include "Objects/Sphere.hpp"

// Scene instance
CrashScene::CrashScene() : BaseScene() {
    _create_shapes();
    _cook_shapes();
}

void CrashScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    m_camera.modelview  = glm::lookAt(glm::vec3(0.0f, 3.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_camera.projection = glm::perspective(glm::radians<float>(25.0f), (float)width / height, 0.1f, 100.0f);
}

void CrashScene::draw() {
    // Static objects
    m_shapes["sceneGround"]->as<Facette>()->draw(m_camera);

    // Draw texts
    TextEngine::Write("Crash scene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void CrashScene::_create_shapes() {
    // Data
    const glm::vec3 pOrigin(0.f, 0.f, 0.f);

    const glm::vec3 uDirect(1.f, 0.f, 0.f);
    const glm::vec3 uNormal(0.f, 1.f, 0.f);
    const glm::vec3 uHeight(0.f, 0.f, 1.f);

    const float cst_plank = 1e-3f;
    const float infinity = 1e+1f;

    // Create
    m_shapes["sceneGround"] = std::make_shared<Facette>(pOrigin - cst_plank*uHeight, uDirect, uNormal);
}

void CrashScene::_cook_shapes() {
    // Data
    const glm::vec4 borderColor(0.7f, 0.7f, 0.7f, 1.0f);
    const glm::vec4 groundColor(1.0f, 0.7f, 0.3f, 1.0f);

    // Cook
    m_shapes["sceneGround"]->as<Facette>()->addRecipe(Cookable::CookType::Solid, groundColor);

}