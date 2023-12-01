#include "SlimeGame.hpp"

using namespace reactphysics3d;

SlimeGame::SlimeGame() : 
    scene(nullptr),
    groundMeshes({
        glm::vec3(9.0f, 2.0f, 0.5f),

        glm::vec3(2.0f, 2.0f, 0.5f),
        glm::vec3(2.0f, 0.03f, 1.0f),
        glm::vec3(2.0f, 0.03f, 1.0f),
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
    }),
    m_last({})
{
    // Setup items
    groundMeshes[0].body()->position = glm::vec3(-6.0f, 0, -0.5f);

    groundMeshes[1].body()->position = glm::vec3(Game3DLimit - 2.0f, 0, -0.5f);
    groundMeshes[2].body()->position = glm::vec3(Game3DLimit - 2.0f, +2.0f, -0.5f);
    groundMeshes[3].body()->position = glm::vec3(Game3DLimit - 2.0f, -2.0f, -0.5f);

    invisbleWalls[0].body()->position = glm::vec3(+2.5f, 0.0f, 0.0f);

    target.body()->position = glm::vec3(0, 0, +1.0f);
    player.body()->position = glm::vec3(+1.0f, 0, 0);
    zeboss.body()->position = glm::vec3(Game3DLimit - 4.0f + 0.10f, 0, 0);

    ennemies[0].body()->position = glm::vec3(-1.0f, 0, 0.4f);
    ennemies[1].body()->position = glm::vec3(-3.0f, 0, 0);
    ennemies[2].body()->position = glm::vec3(-3.3f, 0, 0);

    ennemies[3].body()->position = glm::vec3(Game2DLimit, 0, 0);

    ennemies[4].body()->position = glm::vec3(-6.5f,  0.0f,  0);

    ennemies[5].body()->position = glm::vec3(-8.0f, +1.4f,  0);
    ennemies[6].body()->position = glm::vec3(-10.0f,  0.0f, 0);
    ennemies[7].body()->position = glm::vec3(-12.0f, -1.0f, 0);
    ennemies[8].body()->position = glm::vec3(-12.0f, +1.0f, 0);

    ennemies[9].body()->position = glm::vec3(Game3DLimit, 0.0f, +0.5f);

    // debug
    target.body()->position = glm::vec3(Game3DLimit, 0, +1.0f);
    player.body()->position = glm::vec3(Game3DLimit +1.0f, 0, 0);
}

void SlimeGame::useScene(std::shared_ptr<SlimeScene> scene_) {
    scene = scene_;

    for (Ground& wall : invisbleWalls) {
        wall.addAs(Physx::BodyType::Static);
    }

    player.addAs(Physx::BodyType::Kinematic);
    target.addAs(Physx::BodyType::Static);

    scene->add(player.body());
    scene->add(target.body());
    scene->add(zeboss.body());
}


void SlimeGame::update(float t_sec, State desired_state) {
    if (!scene)
        return;

    // State change
    if (state != desired_state) {
        _change_state(desired_state);
        last_state_change = t_sec;
    }

    // Update scene
    switch (state)
    {
        case SlimeGame::Intro:  _update_intro(t_sec); break;

        case SlimeGame::Game2D: _update_game2d(t_sec);  break;
        case SlimeGame::Game3D: _update_game3d(t_sec);  break;

        case SlimeGame::BossIntro: _update_bossIntro(t_sec); break;
        case SlimeGame::BossFight: _update_bossFight(t_sec); break;
    }
}

// Called only once
void SlimeGame::_change_state(State new_state) {
    // Save state
    m_last.target   = target.body()->position;;
    m_last.player   = player.body()->position;;
    m_last.light    = scene->lights().empty() ? glm::vec3() : scene->lights()[0]->position;
    m_last.cam_pos  = scene->camera().position;
    m_last.cam_dir  = scene->camera().direction;

    // Change
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

        // Add elements
        for (Ground& ground : groundMeshes) {
            ground.addAs(Physx::BodyType::Static);
            scene->add(ground.body());
        }

        for (Ennemy& ennemy : ennemies) {
            ennemy.addAs(Physx::BodyType::Kinematic);
            scene->add(ennemy.body());
        }
        break;

    case Game3D:
        scene->enable_2d_camera = false;
        scene->lightning(true);

        target.enable_3d = true;
        break;

    case BossIntro:
        scene->enable_2d_camera = false;
        scene->lightning(true);

        groundMeshes[0].removePhysx();
        target.removePhysx();
        player.removePhysx();
        break;

    case BossFight:
        player.addAs(Physx::BodyType::Kinematic);
        zeboss.addAs(Physx::BodyType::Kinematic);
        target.addAs(Physx::BodyType::Kinematic);

        target.pbody()->setLinearVelocity(Vector3(+1.0f, 0.1f, 0.0f));
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

    const glm::vec3& player_pos = player.body()->position;
    const glm::vec3& target_pos = target.body()->position;

    float r = glm::clamp(1.0f - 0.5f*t_sec, 0.0f, 1.0f);

    double rho = 1.0f;
    double theta = 0.25f * player_pos.y * 6.28f;

    camera.position = glm::vec3(target_pos.x + rho * cos(theta), target_pos.y + 4.0f + rho * sin(theta), +0.5f);
    camera.direction = glm::vec3(target_pos.x, 0.0f, +0.5f);

    player.update();
    target.update();
    for (Ennemy& ennemy : ennemies)
        ennemy.update();

    if (r > 0)
        scene->lights()[0]->position = glm::vec3(0, 0, 0.5f) + r * target.body()->position + (1.0f - r) * player.body()->position;
    else
        scene->lights()[0]->position = player.body()->position + glm::vec3(0, 0, 0.5f);
}

void SlimeGame::_update_bossIntro(float t_sec) 
{
    Camera& camera = scene->camera();

    const glm::vec3 center = groundMeshes[1].body()->position;
    const float r = glm::clamp(1.0f - (t_sec - last_state_change) / IntroDuration, 0.0f, 1.0f);

    // Animation
    groundMeshes[0].body()->position += glm::vec3(0.02f, 0.0f, 0.0f);

    target.body()->position = r * m_last.target + (1-r) * glm::vec3(center.x, center.y, 0.05f);
    player.body()->position = r * m_last.player + (1-r) * glm::vec3(Game3DLimit - 0.10f, center.y, 0.0f);

    scene->lights()[0]->position = r * m_last.light + (1-r) * (target.body()->position + glm::vec3(0, 0, 0.15f));

    camera.position  = r * m_last.cam_pos + (1-r) * player.body()->position + glm::vec3(5.0f, 0.0f, 4.0f);
    camera.direction = r * m_last.cam_dir + (1-r) * target.body()->position;

    for (Ennemy& ennemy : ennemies) {
        ennemy.pbody()->setLinearVelocity(Vector3(0, 0, -0.6f));
    }
}

void SlimeGame::_update_bossFight(float t_sec)
{
    Camera& camera = scene->camera();

    camera.position  = player.body()->position + glm::vec3(5.0f, 0.0f, 4.0f);
    camera.direction = target.body()->position;

    player.update();
    zeboss.update();
    target.update();

    // Helpers
    auto _Vector3 = [=](const glm::vec3& v3) -> Vector3 
    {
        return Vector3(v3.x, v3.y, v3.z);
    };

    auto _collide = [=](const Vector3& pos, const float size, const Vector3& squarePos, const float dims) -> bool
    {
        if (pos.x + size < squarePos.x - dims) return false;
        if (pos.x - size > squarePos.x + dims) return false;
        if (pos.y + size < squarePos.y - dims) return false;
        if (pos.y - size > squarePos.y + dims) return false;

        return true;
    };

    auto _reflect = [=](const Vector3& u, const Vector3& n) -> Vector3
    {
        auto v2 = Vector2(u.x, u.y) - 2 * (u.x * n.x + u.y * n.y) * Vector2(n.x, n.y);
        return Vector3(v2.x, v2.y, u.z);
    };

    // - Compute physx 2d manually ('cause i'm shit with the lib) -
    Vector3 target_speed    = target.pbody()->getLinearVelocity();
    Vector3 target_pos      = target.pbody()->getTransform().getPosition();
    Vector3 target_npos     = target_pos + target_speed / 60.0f;
    float target_size       = 0.05f;

    Vector3 zeboss_speed    = zeboss.pbody()->getLinearVelocity();
    Vector3 zeboss_pos      = zeboss.pbody()->getTransform().getPosition();
    Vector3 zeboss_npos     = zeboss_pos + zeboss_speed / 60.0f;
    float zeboss_size       = 0.10f;

    Vector3 player_speed    = player.pbody()->getLinearVelocity();
    Vector3 player_pos      = player.pbody()->getTransform().getPosition();
    Vector3 player_npos     = player_pos + player_speed / 60.0f;
    float player_size       = 0.10f;

    Vector3 ground_center   = _Vector3(groundMeshes[1].body()->position);
    float ground_size       = 2.0f;

    // Target/Ground
    Vector3 uGravity(0.0f, 0.0f, -10.0f);
    if(!_collide(target_pos, target_size, ground_center, ground_size))
        target_speed += uGravity/60.0f; // falling

    // Target/Players
    if (_collide(target_pos, target_size, zeboss_pos, zeboss_size)) {
        target_speed = _reflect(target_speed, Vector3(+1.0f, 0.0f, 0.0f)); // boum
    }

    if(_collide(target_pos, target_size, player_pos, player_size)) {
        target_speed = _reflect(target_speed, Vector3(-1.0f, 0.0f, 0.0f)); // boum
    }

    // Results
    target.pbody()->setLinearVelocity(target_speed);
}