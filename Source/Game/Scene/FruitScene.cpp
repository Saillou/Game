#include "FruitScene.hpp"

#include "Objects/Facette.hpp"
#include "Objects/Sphere.hpp"

#include <glm/gtx/string_cast.hpp>

// Scene instance
FruitScene::FruitScene() :
    BaseScene()
{
    _create_shapes();
    _cook_shapes();

    // Camera
    _camPos = glm::vec3(0.0f, 3.0f, 0.5f);
    _camDir = glm::vec3(0.0f, 0.0f, 0.5f);
    _angle  = 30.0f;
}

void FruitScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    _camera_update();
}

void FruitScene::moveCameraPosition(float dx, float dy, float dz) {
    _camPos.x += dx;
    _camPos.y += dy;
    _camPos.z += dz;
}
void FruitScene::moveCameraDirection(float dx, float dy, float dz) {
    _camDir.x += dx;
    _camDir.y += dy;
    _camDir.z += dz;
}

void FruitScene::changeCameraPerspective(float dfov) {
    _angle += dfov;
}

void FruitScene::draw() {
    // Position camera
    _camera_update();

    // Static objects
    m_shapes["sceneGround"]->as<Facette>()->draw(m_camera);

    m_shapes["bucketBack"]->as<Facette>()->draw(m_camera);
    m_shapes["bucketWest"]->as<Facette>()->draw(m_camera);
    m_shapes["bucketEast"]->as<Facette>()->draw(m_camera);
    m_shapes["bucketFace"]->as<Facette>()->draw(m_camera);

    // Dynamic objects
    m_shapes["fruitCurrent"]->as<Facette>()->draw(m_camera, glm::vec3(0.0f, 0.0f, 0.7f));

    // Texts
    int score = 0;
    TextEngine::Write("Score: " + std::to_string(score), 10.0f, m_height - 30.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
    TextEngine::Write("Fruits Scene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void FruitScene::_create_shapes() {
    // Data
    const glm::vec3 pOrigin(0.f, 0.f, 0.f);

    const glm::vec3 uDirect(1.f, 0.f, 0.f);
    const glm::vec3 uNormal(0.f, 1.f, 0.f);
    const glm::vec3 uHeight(0.f, 0.f, 1.f);

    const float cst_plank = 1e-3f;
    const float infinity = 1e+1f;

    const float bucketWidth = 0.50f;
    const float bucketHeight = 0.50f;
    const float bucketDepth = 0.10f;

    const float fruitRadius = 0.05f;

    // Create
    m_shapes["sceneGround"] = std::make_shared<Facette>(pOrigin - cst_plank * uHeight, infinity * uDirect, infinity * uNormal);

    m_shapes["bucketWest"] = std::make_shared<Facette>(pOrigin - bucketWidth * uDirect + bucketHeight * uHeight, bucketDepth * uNormal, bucketHeight * uHeight);
    m_shapes["bucketEast"] = std::make_shared<Facette>(pOrigin + bucketWidth * uDirect + bucketHeight * uHeight, bucketDepth * uNormal, bucketHeight * uHeight);
    m_shapes["bucketFace"] = std::make_shared<Facette>(pOrigin - bucketDepth * uNormal + bucketHeight * uHeight, bucketWidth * uDirect, bucketHeight * uHeight);
    m_shapes["bucketBack"] = std::make_shared<Facette>(pOrigin, bucketWidth * uDirect, bucketDepth * uNormal);

    m_shapes["fruitCurrent"] = std::make_shared<Sphere>(pOrigin, fruitRadius);

}
void FruitScene::_cook_shapes() {
    // Data
    const glm::vec4 borderColor(1.0f, 1.0f, 1.0f, 0.2f);
    const glm::vec4 groundColor(1.0f, 0.7f, 0.3f, 1.0f);
    const glm::vec4 bucketColor(0.3f, 0.7f, 1.0f, 1.0f);

    const glm::vec4 fruitColor(1.0f, 0.4f, 0.1f, 1.0f);

    // Cook
    m_shapes["sceneGround"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, groundColor)
        ;


    m_shapes["bucketBack"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, bucketColor)
        ->addRecipe(Facette::CookType::Border, borderColor)
        ;

    m_shapes["bucketWest"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, bucketColor)
        ->addRecipe(Facette::CookType::Border, borderColor)
        ;

    m_shapes["bucketEast"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, bucketColor)
        ->addRecipe(Facette::CookType::Border, borderColor)
        ;

    m_shapes["bucketFace"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, bucketColor * 0.5f)
        ->addRecipe(Facette::CookType::Border, borderColor)
        ;


    m_shapes["fruitCurrent"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, fruitColor)
        ->addRecipe(Facette::CookType::Border, borderColor)
        ;
}

void FruitScene::_camera_update() {
    float aspect = (float)m_width / m_height;

    static bool init = false;
    static glm::mat4 camStart;
    static glm::mat4 camTarget;

    if (!init) {
        camStart    = glm::perspective(glm::radians<float>(_angle), aspect, 0.1f, 100.0f);
        camTarget   = glm::ortho(-aspect, +aspect, -1.0f, 1.0f, 0.1f, 100.0f);

        init = true;

        m_camera.modelview  = glm::lookAt(_camPos, _camDir, glm::vec3(0.0f, 0.0f, 1.0f));
        m_camera.projection = camTarget;
    }

    // Change progressively to identity
    static float speed = 0.001f;
    speed += speed / 20.0f;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float target = camStart[i][j];

            if (abs(m_camera.projection[i][j] - target) < speed) {
                m_camera.projection[i][j] = target;
            }
            else {
                m_camera.projection[i][j] += (m_camera.projection[i][j] < target ? +speed : -speed);
            }
        }
    }
}
