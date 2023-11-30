#include "SlimeGame.hpp"

using namespace reactphysics3d;


// ------------------------ Slime ------------------------
SlimeGame::Slime::Slime()
{
    createBody();
}

void SlimeGame::Slime::update() {
    // Simulate gravity
    constexpr float epsilon = 1e-2f;

    const auto& curr_transform = _pbody->getTransform();
    const auto& curr_position = curr_transform.getPosition();
    const auto& curr_velocity = _pbody->getLinearVelocity();

    if (curr_position.z > epsilon) {
        _pbody->setLinearVelocity(curr_velocity - _jump * Vector3(0, 0, 1e-1f));
    }
    else if (curr_position.z != 0.0f) {
        _pbody->setTransform(Transform(Vector3(curr_position.x, curr_position.y, 0.0f), curr_transform.getOrientation()));
    }
}

void SlimeGame::Slime::move(glm::vec3& direction) {
    const auto& curr_transform = _pbody->getTransform();
    const auto& curr_position  = curr_transform.getPosition();
    const auto& curr_velocity  = _pbody->getLinearVelocity();

    glm::vec3 total = _accel * direction;
    auto new_speed = curr_velocity + Vector3(total.x, total.y, total.z);

    new_speed.x = glm::clamp(new_speed.x, -_maxSpeed, _maxSpeed);
    new_speed.y = glm::clamp(new_speed.y, -_maxSpeed, _maxSpeed);

    // Can't move into the first invisible wall
    if (curr_position.x > 1.9f) {
        if(new_speed.x > 0)
            new_speed.x = 0.0f;
        _pbody->setTransform(Transform(Vector3(1.9f, curr_position.y, curr_position.z), curr_transform.getOrientation()));
    }

    _pbody->setLinearVelocity(new_speed);
}

void SlimeGame::Slime::jump() {
    constexpr float epsilon = 1e-2f;

    if (_pbody->getTransform().getPosition().z > epsilon)
        return;

    auto curr_velocity = _pbody->getLinearVelocity();
    _pbody->setLinearVelocity(curr_velocity + _jump * Vector3(0, 0, 2.0f));
}

const BaseItem::sBody& SlimeGame::Slime::createBody() {
    _body = std::make_shared<SphereBody>(0.10f);
    return _body;
    
}

void SlimeGame::Slime::_onAdd() {
    _pbody->setLinearDamping(5.0f);
}

// ------------------------ Ground ------------------------
SlimeGame::Ground::Ground(const glm::vec3& dims) : 
    m_dims(dims)
{
    createBody();
}

const BaseItem::sBody& SlimeGame::Ground::createBody() {
    _body = std::make_shared<BoxBody>(m_dims);
    return _body;
}

// ------------------------ Target ------------------------
SlimeGame::Target::Target()
{
    createBody();
}

void SlimeGame::Target::update() {
    const auto& curr_transform = _pbody->getTransform();
    const auto& curr_position = curr_transform.getPosition();

    // Force y-coordinate to 0
    if (!enable_3d && curr_position.y != 0.0f) {
        _pbody->setTransform(Transform(
            Vector3(curr_position.x, 0.0f, curr_position.z), 
            curr_transform.getOrientation())
        );
    }
}

const BaseItem::sBody& SlimeGame::Target::createBody() {
    _body = std::make_shared<SphereBody>(0.05f);
    return _body;
}

// ------------------------ Ennemy ------------------------
SlimeGame::Ennemy::Ennemy(float amplitude, float pulse, float phase, const glm::vec3& dir, const glm::vec3& dims):
    _dims(dims),
    _moveDirection(dir),
    _amplitude(amplitude),
    _pulse(pulse),
    _phase(phase)
{
    createBody();
}

void SlimeGame::Ennemy::update() {
    float t = _time.elapsed<Timer::millisecond>() / 1000.0f;
    _pbody->setLinearVelocity
    (
        _amplitude * sin(2 * glm::pi<float>() * _pulse * t + _phase) *
        Vector3(_moveDirection.x, _moveDirection.y, _moveDirection.z)
    );
}

const BaseItem::sBody& SlimeGame::Ennemy::createBody() {
    _body = std::make_shared<BoxBody>(_dims);
    return _body;
}

// ------------------------ Implementation ------------------------
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
    groundMeshes[0].body()->position = glm::vec3(-8.0f, 0, -0.5f);

    invisbleWalls[0].body()->position = glm::vec3(+2.5f, 0.0f, 0.0f);

    target.body()->position = glm::vec3(0, 0, +1.0f);
    player.body()->position = glm::vec3(+1.0f, 0, 0);

    ennemies[0].body()->position = glm::vec3(-1.0f, 0, 0.4f);
    ennemies[1].body()->position = glm::vec3(-3.0f, 0, 0);
    ennemies[2].body()->position = glm::vec3(-3.3f, 0, 0);

    ennemies[3].body()->position = glm::vec3(-4.0f, 0, 0);

    ennemies[4].body()->position = glm::vec3(-6.5f,  0.0f,  0);

    ennemies[5].body()->position = glm::vec3(-8.0f, +1.4f,  0);
    ennemies[6].body()->position = glm::vec3(-10.0f,  0.0f, 0);
    ennemies[7].body()->position = glm::vec3(-12.0f, -1.0f, 0);
    ennemies[8].body()->position = glm::vec3(-12.0f, +1.0f, 0);

    ennemies[9].body()->position = glm::vec3(-14.0f, 0.0f,  +0.5f);

    /* todo: 
        detection of scene changes
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

void SlimeGame::update(float t_sec,  SlimeScene::State desired_state) {
    if (!scene)
        return;

    // Camera
    Camera& camera = scene->camera();

//#define TEST
#ifdef TEST
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
    // Changement
    if (scene->state != desired_state) {
        switch (desired_state)
        {
        case SlimeScene::Intro:
            scene->enable_2d_camera = false;
            scene->lightning(false);

            break;

        case SlimeScene::Game2D:
            scene->enable_2d_camera = true;
            scene->lightning(false);

            target.enable_3d = false;
            target.setType(Physx::BodyType::Dynamic);
            break;

        case SlimeScene::Game3D:
            scene->enable_2d_camera = false;
            scene->lightning(true);

            target.enable_3d = true;
            break;

        case SlimeScene::Boss:
            scene->enable_2d_camera = true;
            scene->lightning(true);
            break;

        default:
            break;
        }
        // Apply
        scene->state = desired_state;
    }

    // Update
    switch (scene->state)
    {
    case SlimeScene::Intro:
        {
            static const float beg_time = SlimeScene::StartTime.at(SlimeScene::State::Intro);
            static const float end_time = SlimeScene::StartTime.at(SlimeScene::State::Game2D);
            const float rel_time = (t_sec - beg_time) / (end_time - beg_time);

            float r = glm::clamp(1.0f - rel_time, 0.0f, 1.0f);

            camera.position = r * glm::vec3(0.0f, 0.1f, +1.0f) + (1.0f - r) * glm::vec3(0.0f, 4.0f, +0.5f);

            break;
        }
    case SlimeScene::State::Game2D: 
        {
            static const float beg_time = SlimeScene::StartTime.at(SlimeScene::State::Game2D);
            const glm::vec3& target_pos = target.body()->position;
           
            float r = glm::clamp(1.0f - 3.0f * (t_sec - beg_time), 0.0f, 1.0f);
            
            camera.position  = glm::vec3(target_pos.x, 4.0f, +0.5f);

            if(r > 0)
                camera.direction = glm::vec3(0.0f, 0.0f, 0.5f + 0.5f*r);
            else
                camera.direction = glm::vec3(target_pos.x, 0.0f, +0.5f);

            player.update();
            target.update();
            for (Ennemy& ennemy : ennemies)
                ennemy.update();

            break;
        }
    case SlimeScene::State::Game3D:
        {
            static const float beg_time = SlimeScene::StartTime.at(SlimeScene::State::Game3D);
            const glm::vec3& player_pos = player.body()->position;
            const glm::vec3& target_pos = target.body()->position;

            float r = glm::clamp(1.0f - 0.5f*(t_sec - beg_time), 0.0f, 1.0f);
            
            double rho   = 1.0f;
            double theta = 0.25f*player_pos.y * 6.28f;

            camera.position = glm::vec3(target_pos.x + rho * cos(theta), target_pos.y + 4.0f + rho * sin(theta), +0.5f);
            camera.direction = glm::vec3(target_pos.x, 0.0f, +0.5f);

            player.update();
            target.update();
            for (Ennemy& ennemy : ennemies)
                ennemy.update();

            if (r > 0)
                scene->lights()[0]->position = glm::vec3(0, 0, 0.5f) +
                    r *          target.body()->position +
                    (1.0f - r) * player.body()->position;
            else
                scene->lights()[0]->position = player.body()->position + glm::vec3(0, 0, 0.5f);
                
            break;
        }
    case SlimeScene::State::Boss:
    {
        static const float beg_time = SlimeScene::StartTime.at(SlimeScene::State::Boss);
        const float rel_time = (t_sec - beg_time);

        float r = glm::clamp(1.0f - rel_time, 0.0f, 1.0f);

        player.update();
        target.update();
        for (Ennemy& ennemy : ennemies)
            ennemy.update();

        if (!scene->lights().empty()) {
            scene->lights()[0]->position = r * target.body()->position + (1.0f - r) * (target.body()->position + glm::vec3(0.0f, 0.0f, +.5f));
        }

        break;
    }
    }
#endif
}
