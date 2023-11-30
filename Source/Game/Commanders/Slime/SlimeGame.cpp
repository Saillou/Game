#include "SlimeGame.hpp"


SlimeGame::SlimeGame() : 
    scene(nullptr),
    groundMeshes({
        glm::vec3(10.0f, 2.0f, 0.5f)
    }),
    invisbleWalls({
        glm::vec3(0.5f, 2.0, 10.0f)
    }),
    ennemies({
        Ennemy(0.3f, 0.2f, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f), 0.05f * glm::vec3(1.f, 1.f, 3.f)),
        Ennemy(0.5f, 0.4f, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f), 0.05f * glm::vec3(1.f, 1.f, 3.f)),
        Ennemy(0.5f, 0.8f, 1.0f, glm::vec3(0.0f, 0.0f, 1.0f), 0.05f * glm::vec3(1.f, 1.f, 3.f)),

        Ennemy(0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.00f * glm::vec3(0.05f, 0.05f, 3.f)),

        Ennemy(0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.00f * glm::vec3(0.05f, 0.35f, 10.f)),

        Ennemy(0.5f, 0.4f, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), 1.00f * glm::vec3(0.02f, 0.50f, 1.f)),
        Ennemy(6.0f, 0.8f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), 1.00f * glm::vec3(0.02f, 0.50f, 1.f)),
        Ennemy(0.0f, 0.0f, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), 1.00f * glm::vec3(0.02f, 0.35f, 1.f)),
        Ennemy(0.0f, 0.0f, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), 1.00f * glm::vec3(0.02f, 0.35f, 1.f)),

        Ennemy(0.5f, 0.1f, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f), 1.00f * glm::vec3(0.01f, 2.00f, 0.4f)),
    })
{
    // Setup items
    groundMeshes[0].body()->position = glm::vec3(-7.75f, 0, -0.5f);

    invisbleWalls[0].body()->position = glm::vec3(+2.5f, 0.0f, 0.0f);

    target.body()->position = glm::vec3(0, 0, +1.0f);
    player.body()->position = glm::vec3(+1.0f, 0, 0);

    ennemies[0].body()->position = glm::vec3(-1.0f, 0, 0.4f);
    ennemies[1].body()->position = glm::vec3(-3.0f, 0, 0);
    ennemies[2].body()->position = glm::vec3(-3.3f, 0, 0);

    ennemies[3].body()->position = glm::vec3(Game2DLimit, 0, 0);

    ennemies[4].body()->position = glm::vec3(-6.5f,  0.0f,  0);

    ennemies[5].body()->position = glm::vec3(-8.0f, +1.4f,  0);
    ennemies[6].body()->position = glm::vec3(-10.0f,  0.0f, 0);
    ennemies[7].body()->position = glm::vec3(-12.0f, -1.0f, 0);
    ennemies[8].body()->position = glm::vec3(-12.0f, +1.0f, 0);

    ennemies[9].body()->position = glm::vec3(Game3DLimit, 0.0f,  +0.5f);

    /* todo: 
        add fall detection -> refresh if state < boss | else win
        add boss arena -> make wall fall and boss appears
        boss physics
    */
}

void SlimeGame::useScene(std::shared_ptr<SlimeScene> scene_) {
    scene = scene_;
    if (!scene)
        throw "Kabooum";

    for (Ground& ground : groundMeshes) {
        ground.addAs(Physx::BodyType::Static);
        scene->add(ground.body());
    }

    for (Ground& wall : invisbleWalls) {
        wall.addAs(Physx::BodyType::Static);
    }

    for (Ennemy& ennemy : ennemies) {
        ennemy.addAs(Physx::BodyType::Kinematic);
        scene->add(ennemy.body());
    }

    player.addAs(Physx::BodyType::Kinematic);
    target.addAs(Physx::BodyType::Static);

    scene->add(player.body());
    scene->add(target.body());
}


void SlimeGame::update(float t_sec, State desired_state) {
    if (!scene)
        return;

//#define TEST
#ifdef TEST
    Camera& camera = scene->camera();

    // - - - - - - - - - - - - test - - - - - - - - - - - -
    camera.position  = target.body()->position + glm::vec3(0.0f, 10.0f, +5.0f);
    camera.direction = target.body()->position;
    camera.direction.y = 0.0f;

    scene->enable_2d_camera = false;
    scene->lightning(true);

    target.setType(Physx::BodyType::Dynamic);

    player.update();
    target.update();

    for(Ennemy& ennemy: ennemies)
        ennemy.update();
    // - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
    // State change
    if (state != desired_state)
        _change_state(desired_state);

    // Update scene
    switch (state)
    {
        case SlimeGame::Intro:  _update_intro(t_sec);   break;
        case SlimeGame::Game2D: _update_game2d(t_sec);  break;
        case SlimeGame::Game3D: _update_game3d(t_sec);  break;
        case SlimeGame::Boss:   _update_boss(t_sec);    break;
    }
#endif
}

// Called only once
void SlimeGame::_change_state(State new_state) {
    switch (new_state)
    {
    case Intro:
        scene->enable_2d_camera = false;
        scene->lightning(false);

        break;

    case Game2D:
        scene->enable_2d_camera = true;
        scene->lightning(false);

        target.enable_3d = false;
        target.setType(Physx::BodyType::Dynamic);
        break;

    case Game3D:
        scene->enable_2d_camera = false;
        scene->lightning(true);

        target.enable_3d = true;
        break;

    case Boss:
        scene->enable_2d_camera = true;
        scene->lightning(true);
        break;

    default:
        break;
    }

    // Apply
    state = new_state;
}

// Called each new frames
void SlimeGame::_update_intro(float t_sec) {
    float r = glm::clamp(1.0f - t_sec / IntroDuration, 0.0f, 1.0f);

    scene->camera().position = r * glm::vec3(0.0f, 0.1f, +1.0f) + (1.0f - r) * glm::vec3(0.0f, 4.0f, +0.5f);
}

void SlimeGame::_update_game2d(float t_sec) 
{
    Camera& camera = scene->camera();

    static const float beg_time = IntroDuration;
    const glm::vec3& target_pos = target.body()->position;

    float r = glm::clamp(1.0f - 3.0f * (t_sec - beg_time), 0.0f, 1.0f);

    camera.position = glm::vec3(target_pos.x, 4.0f, +0.5f);

    if (r > 0)
        camera.direction = glm::vec3(0.0f, 0.0f, 0.5f + 0.5f * r);
    else
        camera.direction = glm::vec3(target_pos.x, 0.0f, +0.5f);

    player.update();
    target.update();
    for (Ennemy& ennemy : ennemies)
        ennemy.update();
}

void SlimeGame::_update_game3d(float t_sec) 
{
    Camera& camera = scene->camera();

    static const float beg_time = 0.0f;
    const glm::vec3& player_pos = player.body()->position;
    const glm::vec3& target_pos = target.body()->position;

    float r = glm::clamp(1.0f - 0.5f * (t_sec - beg_time), 0.0f, 1.0f);

    double rho = 1.0f;
    double theta = 0.25f * player_pos.y * 6.28f;

    camera.position = glm::vec3(target_pos.x + rho * cos(theta), target_pos.y + 4.0f + rho * sin(theta), +0.5f);
    camera.direction = glm::vec3(target_pos.x, 0.0f, +0.5f);

    player.update();
    target.update();
    for (Ennemy& ennemy : ennemies)
        ennemy.update();

    if (r > 0)
        scene->lights()[0]->position = glm::vec3(0, 0, 0.5f) +
        r * target.body()->position +
        (1.0f - r) * player.body()->position;
    else
        scene->lights()[0]->position = player.body()->position + glm::vec3(0, 0, 0.5f);
}

void SlimeGame::_update_boss(float t_sec) 
{
    Camera& camera = scene->camera();

    static const float beg_time = 0.0f;
    const float rel_time = (t_sec - beg_time);

    float r = glm::clamp(1.0f - rel_time, 0.0f, 1.0f);

    player.update();
    target.update();
    for (Ennemy& ennemy : ennemies)
        ennemy.update();

    if (!scene->lights().empty()) {
        scene->lights()[0]->position = r * target.body()->position + (1.0f - r) * (target.body()->position + glm::vec3(0.0f, 0.0f, +.5f));
    }
}