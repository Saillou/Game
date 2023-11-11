#include "SlimeScene.hpp"

#include "Objects/Parallelepiped.hpp"
#include "Objects/Facette.hpp"
#include "Objects/Sphere.hpp"

// Scene instance
SlimeScene::SlimeScene() : BaseScene() {
    _create_shapes();
    _cook_shapes();
}

void SlimeScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    m_camera.modelview  = glm::lookAt(glm::vec3(0.0f, 3.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_camera.projection = glm::perspective(glm::radians<float>(30.0f), (float)width / height, 0.1f, 100.0f);
}

void SlimeScene::draw() {
    // Static objects
    m_shapes["sceneGround"]->as<Facette>()->draw(m_camera);

    m_shapes["westGoal_l"]->as<Facette>()->draw(m_camera);
    m_shapes["westGoal_r"]->as<Facette>()->draw(m_camera);
    m_shapes["westGoal_f"]->as<Facette>()->draw(m_camera);
     
    m_shapes["eastGoal_l"]->as<Facette>()->draw(m_camera);
    m_shapes["eastGoal_r"]->as<Facette>()->draw(m_camera);
    m_shapes["eastGoal_f"]->as<Facette>()->draw(m_camera);

    // Player
    m_shapes["westPlayer"]->as<Parallelepiped>()->draw(m_camera);
    m_shapes["eastPlayer"]->as<Parallelepiped>()->draw(m_camera);

    // Dynamic objects
    m_shapes["ball"]->as<Sphere>()->draw(m_camera, glm::vec3(0,0,0.05f));

    // Texts
    int score_w = 0;
    int score_e = 0;
    TextEngine::Write("Score: " + std::to_string(score_w) + "|" +std::to_string(score_e), 10.0f, m_height - 30.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
    TextEngine::Write("Slime scene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void SlimeScene::_create_shapes() {
    // Data
    const glm::vec3 pOrigin(0.f, 0.f, 0.f);

    const glm::vec3 uDirect(1.f, 0.f, 0.f);
    const glm::vec3 uNormal(0.f, 1.f, 0.f);
    const glm::vec3 uHeight(0.f, 0.f, 1.f);

    const float cst_plank = 1e-3f;
    const float infinity  = 1e+1f;

    const float fieldWidth = 1.20f;

    const float goalWidth  = 0.50f;
    const float goalHeight = 0.15f;
    const float goalDepth  = 0.05f;

    const float playerWidth  = 0.075f;
    const float playerDepth  = 0.050f;
    const float playerHeight = 0.070f;

    const float fruitRadius = 0.05f;

    const glm::vec3 pWestGoal = pOrigin + uDirect*fieldWidth + goalHeight*uHeight;
    const glm::vec3 pEastGoal = pOrigin - uDirect*fieldWidth + goalHeight*uHeight;


    // Create
    m_shapes["sceneGround"] = std::make_shared<Facette>(pOrigin - cst_plank*uHeight, infinity*uDirect, infinity*uNormal);

    m_shapes["westGoal_l"] = std::make_shared<Facette>(pWestGoal - goalDepth*uDirect - goalWidth*uNormal, goalDepth * uDirect, goalHeight * uHeight);
    m_shapes["westGoal_r"] = std::make_shared<Facette>(pWestGoal - goalDepth*uDirect + goalWidth*uNormal, goalDepth * uDirect, goalHeight * uHeight);
    m_shapes["westGoal_f"] = std::make_shared<Facette>(pWestGoal, goalWidth*uNormal, goalHeight*uHeight);

    m_shapes["eastGoal_r"] = std::make_shared<Facette>(pEastGoal + goalDepth*uDirect - goalWidth*uNormal, goalDepth * uDirect, goalHeight * uHeight);
    m_shapes["eastGoal_l"] = std::make_shared<Facette>(pEastGoal + goalDepth*uDirect + goalWidth*uNormal, goalDepth * uDirect, goalHeight * uHeight);
    m_shapes["eastGoal_f"] = std::make_shared<Facette>(pEastGoal, goalWidth*uNormal, goalHeight*uHeight);

    m_shapes["ball"] = std::make_shared<Sphere>(pOrigin, fruitRadius);

    m_shapes["westPlayer"] = std::make_shared<Parallelepiped>(pWestGoal - goalDepth * uDirect - playerHeight * uHeight, playerWidth*uDirect, playerDepth * uNormal, playerHeight * uHeight);
    m_shapes["eastPlayer"] = std::make_shared<Parallelepiped>(pEastGoal + goalDepth * uDirect - playerHeight * uHeight, playerWidth*uDirect, playerDepth * uNormal, playerHeight * uHeight);
}

void SlimeScene::_cook_shapes() {
    // Data
    const glm::vec4 borderColor(0.7f, 0.7f, 0.7f, 1.0f);
    const glm::vec4 groundColor(1.0f, 0.7f, 0.3f, 1.0f);
    const glm::vec4 bucketColor(0.3f, 0.7f, 1.0f, 1.0f);
    const glm::vec4 playerColor(0.7f, 0.7f, 0.7f, 1.0f);
    const glm::vec4 ballColor(1.0f, 0.4f, 0.1f, 1.0f);

    // Cook
    m_shapes["sceneGround"]->as<Facette>()->addRecipe(Facette::CookType::Solid, groundColor);

    // wgoal
    m_shapes["westGoal_l"]->as<Facette>()
        ->addRecipe(Facette::CookType::Border, borderColor)
        ->addRecipe(Facette::CookType::Solid, bucketColor);

    m_shapes["westGoal_r"]->as<Facette>()
        ->addRecipe(Facette::CookType::Border, borderColor)
        ->addRecipe(Facette::CookType::Solid, bucketColor);

    m_shapes["westGoal_f"]->as<Facette>()
        ->addRecipe(Facette::CookType::Border, borderColor)
        ->addRecipe(Facette::CookType::Solid, bucketColor*0.5f);

    // egoal
    m_shapes["eastGoal_l"]->as<Facette>()
        ->addRecipe(Facette::CookType::Border, borderColor)
        ->addRecipe(Facette::CookType::Solid, bucketColor);

    m_shapes["eastGoal_r"]->as<Facette>()
        ->addRecipe(Facette::CookType::Border, borderColor)
        ->addRecipe(Facette::CookType::Solid, bucketColor);

    m_shapes["eastGoal_f"]->as<Facette>()
        ->addRecipe(Facette::CookType::Border, borderColor)
        ->addRecipe(Facette::CookType::Solid, bucketColor*0.5f);

    // Player
    m_shapes["westPlayer"]->as<Parallelepiped>()
        ->addRecipe(Parallelepiped::CookType::Border, borderColor)
        ->addRecipe(Parallelepiped::CookType::Solid, playerColor);

    m_shapes["eastPlayer"]->as<Parallelepiped>()
        ->addRecipe(Parallelepiped::CookType::Border, borderColor)
        ->addRecipe(Parallelepiped::CookType::Solid, glm::vec4(1.0f, 1.0f, 1.0f, 2*playerColor.a) - playerColor);

    // ball
    m_shapes["ball"]->as<Facette>()
        ->addRecipe(Facette::CookType::Border, ballColor*0.7f)
        ->addRecipe(Facette::CookType::Solid, ballColor);
}