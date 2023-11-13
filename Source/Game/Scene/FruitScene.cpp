#include "FruitScene.hpp"

#include "Objects/Facette.hpp"

#include <glm/gtx/string_cast.hpp>

// Object instances
Fruit::Fruit(float radius_, const glm::vec3& pos_, const glm::vec4& color_):
    SphereBody(radius_, pos_, color_)
{
    // ..
}

Wall::Wall(const glm::vec3& pos, const glm::vec3& u, const glm::vec3& n, const glm::vec4& color_):
    FacetteBody(pos, u, n, color_)
{
    // ..
}


// Scene instance
FruitScene::FruitScene() :
    BaseScene()
{
    _create_shapes();
    _cook_shapes();

    // Camera
    m_camera.position  = glm::vec3(0.0f, 3.0f, 0.5f);
    m_camera.direction = glm::vec3(0.0f, 0.0f, 0.5f);
    m_camera.fieldOfView = 30.0f;
}

void FruitScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    _camera_update();
}

void FruitScene::addWall(std::shared_ptr<Wall> wall) {
    m_walls.push_back(wall);
}

void FruitScene::addFruit(std::shared_ptr<Fruit> fruit) {
    m_fruits.push_back(fruit);
}

void FruitScene::draw() {
    // Get camera
    _camera_update();

    // Static objects - No physx
    m_shapes["sceneGround"]->as<Facette>()->draw(m_camera);
    m_shapes["sceneFrame"]->as<Facette>()->draw(m_camera);
    m_shapes["bucketFace"]->as<Facette>()->draw(m_camera);

    // Static objects - With physx
    for (auto& wall : m_walls) {
        wall->draw(m_camera);
    }

    // Dynamic objects - With physx
    for (auto& fruit: m_fruits) {
        fruit->draw(m_camera);
    }

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
    const float infinity  = 1e+1f;

    const float bucketWidth  = 0.50f;
    const float bucketHeight = 0.50f;
    const float bucketDepth  = 0.10f;

    // Create
    m_shapes["sceneGround"] = std::make_shared<Facette>(pOrigin - cst_plank * uHeight, infinity * uDirect, infinity * uNormal);
    m_shapes["sceneFrame"]  = std::make_shared<Facette>(pOrigin - uNormal, infinity*uDirect, infinity*uHeight);
    m_shapes["bucketFace"]  = std::make_shared<Facette>(pOrigin - 0.9f*bucketDepth * uNormal + bucketHeight * uHeight, bucketWidth * uDirect, bucketHeight * uHeight);
}

void FruitScene::_cook_shapes() {
    // Data
    const glm::vec4 borderColor(1.0f, 1.0f, 1.0f, 0.2f);
    const glm::vec4 groundColor(1.0f, 0.7f, 0.3f, 1.0f);
    const glm::vec4 bucketColor(0.3f, 0.7f, 1.0f, 1.0f);

    // Cook
    m_shapes["sceneGround"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, groundColor);

    m_shapes["sceneFrame"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, groundColor * 0.5f);

    m_shapes["bucketFace"]->as<Facette>()
        ->addRecipe(Facette::CookType::Solid, bucketColor * 0.5f)
        ->addRecipe(Facette::CookType::Border, borderColor);
}

void FruitScene::_camera_update() {
    float aspect = (float)m_width / m_height;

    static bool init = false;
    static glm::mat4 camStart;
    static glm::mat4 camTarget;

    if (!init) {
        camStart    = m_camera.perspective(aspect);
        camTarget   = m_camera.ortho(aspect);

        init = true;

        m_camera.modelview  = m_camera.lookAt(glm::vec3(0, 0, 1));
        m_camera.projection = camTarget;
    }
    return;

    // Test: Change progressively to identity
    static float speed = 0.001f;
    speed += speed / 20.0f;

    bool ended = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float target = camStart[i][j];

            if (abs(m_camera.projection[i][j] - target) < speed) {
                m_camera.projection[i][j] = target;
            }
            else {
                m_camera.projection[i][j] += (m_camera.projection[i][j] < target ? +speed : -speed);
                ended = false;
            }
        }
    }

    if (ended) {
        auto tmp = camStart;

        camStart = camTarget;
        camTarget = tmp;

        speed = 0.001f;
    }
}
