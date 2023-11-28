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
    glm::vec3 total = _accel * direction;
    auto new_speed = _pbody->getLinearVelocity() + Vector3(total.x, total.y, total.z);

    new_speed.x = glm::clamp(new_speed.x, -_maxSpeed, _maxSpeed);
    new_speed.y = glm::clamp(new_speed.y, -_maxSpeed, _maxSpeed);

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
    _pbody->setLinearDamping(10.0f);
}

// ------------------------ Ground ------------------------
SlimeGame::Ground::Ground()
{
    createBody();
}

const BaseItem::sBody& SlimeGame::Ground::createBody() {
    const glm::vec3 dims(5.0f, 2.0f, 0.5f);

    _body = std::make_shared<BoxBody>(dims);
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
    const auto& curr_velocity = _pbody->getLinearVelocity();

    // Force y-coordinate to 0
    if (curr_position.y != 0.0f) {
        _pbody->setTransform(Transform(Vector3(curr_position.x, 0.0f, curr_position.z), curr_transform.getOrientation()));
    }
}

const BaseItem::sBody& SlimeGame::Target::createBody() {
    _body = std::make_shared<SphereBody>(0.05f);
    return _body;
}

// ------------------------ Ennemy ------------------------
SlimeGame::Ennemy::Ennemy()
{
    createBody();
}

void SlimeGame::Ennemy::update() {
    float t = _time.elapsed<Timer::millisecond>() / 1000.0f;
    const float A = 0.5f; // Amplitude (pix/vp)
    const float w = 0.2f; // Period (s^-1)

    _pbody->setLinearVelocity(Vector3(0, 0, A*sin(2*glm::pi<float>()*w*t)));
}

const BaseItem::sBody& SlimeGame::Ennemy::createBody() {
    _body = std::make_shared<BoxBody>(0.05f * glm::vec3(1.f, 1.f, 3.f));
    return _body;
}

// ------------------------ Implementation ------------------------
SlimeGame::SlimeGame() : scene(nullptr) {
    // Setup items
    ground.body()->position = glm::vec3(0, 0, -0.5f);
    target.body()->position = glm::vec3(0, 0, +1.0f);
    player.body()->position = glm::vec3(+1.0f, 0, 0);
    ennemy.body()->position = glm::vec3(-1.0f, 0, 0);
}

void SlimeGame::useScene(std::shared_ptr<SlimeScene> scene_) {
    scene = scene_;
    if (!scene)
        throw "Kabooum";

    ground.addAs(Physx::BodyType::Static);
    ennemy.addAs(Physx::BodyType::Kinematic);
    player.addAs(Physx::BodyType::Kinematic);
    target.addAs(Physx::BodyType::Static);

    scene->add(ground.body());
    scene->add(ennemy.body());
    scene->add(player.body());
    scene->add(target.body());
}

void SlimeGame::update(float t_sec,  SlimeScene::State desired_state) {
    if (!scene)
        return;

    // Camera
    Camera& camera = scene->camera();

    // -- test --
    camera.position  = glm::vec3(0.0f, 3.8f, +0.5f);
    camera.direction = glm::vec3(0.0f, 0.0f, +0.5f);

    scene->enable_2d_camera = true;
    scene->lightning(false);

    target.setType(Physx::BodyType::Dynamic);

    player.update();
    target.update();
    ennemy.update();
    //return;
    // ----------

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

            target.setType(Physx::BodyType::Dynamic);
            break;

        case SlimeScene::Game3D:
            scene->enable_2d_camera = false;
            scene->lightning(true);

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

            camera.position = r * glm::vec3(0.0f, 0.1f, +1.0f) + (1.0f - r) * glm::vec3(0.0f, 3.8f, +0.5f);

            break;
        }
    case SlimeScene::State::Game2D: 
        {
            static const float beg_time = SlimeScene::StartTime.at(SlimeScene::State::Game2D);
            const float rel_time = 3.0f*(t_sec - beg_time);

            float r = glm::clamp(1.0f - rel_time, 0.0f, 1.0f);

            camera.direction = r * glm::vec3(0.0f, 0.0f, +1.0f) + (1.0f - r) * glm::vec3(0.0f, 0.0f, +0.5f);

            player.update();
            target.update();
            break;
        }
    case SlimeScene::State::Game3D:
        {
            static const float beg_time = SlimeScene::StartTime.at(SlimeScene::State::Game3D);
            const float rel_time = (t_sec - beg_time);

            float r = glm::clamp(1.0f - rel_time, 0.0f, 1.0f);

            camera.position = r * glm::vec3(0.0f, 3.8f, +0.5f) + (1.0f - r) * glm::vec3(0.0f, 5.0f, +2.0f);
            camera.direction = r * glm::vec3(0.0f, 0.0f, +0.5f) + (1.0f - r) * glm::vec3(0.0f, 0.0f, +0.0f);

            player.update();
            target.update();

            if (!scene->lights().empty()) {
                scene->lights()[0]->position = target.body()->position;
            }

            break;
        }
    case SlimeScene::State::Boss:
    {
        static const float beg_time = SlimeScene::StartTime.at(SlimeScene::State::Boss);
        const float rel_time = (t_sec - beg_time);

        float r = glm::clamp(1.0f - rel_time, 0.0f, 1.0f);

        player.update();
        target.update();

        if (!scene->lights().empty()) {
            scene->lights()[0]->position = r * target.body()->position + (1.0f - r) * (target.body()->position + glm::vec3(0.0f, 0.0f, +.5f));
        }

        break;
    }
    }
}
