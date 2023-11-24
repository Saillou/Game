#include "SlimeGame.hpp"

using namespace reactphysics3d;


// ------------------------ Base ------------------------
BaseItem::BaseItem():
    _body(nullptr),
    _pbody(nullptr)
{ }

// Getters
BaseItem::sBody BaseItem::body() const {
    return _body;
}

// Methods
void BaseItem::addTo(std::shared_ptr<SlimeScene> scene, Physx::BodyType type) {
    scene->add(_body ? _body : createBody());
    _pbody = Physx::Add(_body, type);
    _onAdd();
}

void BaseItem::_onAdd() {
    // to be overrided
}

// ------------------------ Slime ------------------------
Slime::Slime()
{
    createBody();
}

void Slime::update() {
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

void Slime::move(glm::vec3& direction) {
    glm::vec3 total = _accel * direction;
    auto new_speed = _pbody->getLinearVelocity() + Vector3(total.x, total.y, total.z);

    new_speed.x = glm::clamp(new_speed.x, -_maxSpeed, _maxSpeed);
    new_speed.y = glm::clamp(new_speed.y, -_maxSpeed, _maxSpeed);

    _pbody->setLinearVelocity(new_speed);
}

void Slime::jump() {
    constexpr float epsilon = 1e-2f;

    if (_pbody->getTransform().getPosition().z > epsilon)
        return;

    auto curr_velocity = _pbody->getLinearVelocity();
    _pbody->setLinearVelocity(curr_velocity + _jump * Vector3(0, 0, 2.0f));
}

const BaseItem::sBody& Slime::createBody() {
    _body = std::make_shared<SphereBody>(0.10f);
    return _body;
    
}

void Slime::_onAdd() {
    _pbody->setLinearDamping(10.0f);
}

// ------------------------ Ground ------------------------
Ground::Ground()
{
    createBody();
}

const BaseItem::sBody& Ground::createBody() {
    const glm::vec3 dims(5.0f, 2.0f, 0.5f);

    _body = std::make_shared<BoxBody>(dims);
    return _body;
}

// ------------------------ Target ------------------------
Target::Target()
{
    createBody();
}

void Target::update() {
    const auto& curr_transform = _pbody->getTransform();
    const auto& curr_position = curr_transform.getPosition();
    const auto& curr_velocity = _pbody->getLinearVelocity();

    // Force y-coordinate to 0
    if (curr_position.y != 0.0f) {
        _pbody->setTransform(Transform(Vector3(curr_position.x, 0.0f, curr_position.z), curr_transform.getOrientation()));
    }
}

const BaseItem::sBody& Target::createBody() {
    _body = std::make_shared<SphereBody>(0.05f);
    return _body;
}

// ------------------------ Implementation ------------------------
SlimeGame::SlimeGame() {
    // Setup items
    ground.body()->position = glm::vec3(0, 0, -0.5f);
    target.body()->position = glm::vec3(0, 0, +1.0f);
    player.body()->position = glm::vec3(+1.0f, 0, 0);
    ennemy.body()->position = glm::vec3(-1.0f, 0, 0);
}

void SlimeGame::useScene(std::shared_ptr<SlimeScene> scene) {
    ground.addTo(scene, Physx::BodyType::Static);
    ennemy.addTo(scene, Physx::BodyType::Static);
    player.addTo(scene, Physx::BodyType::Kinematic);
    target.addTo(scene, Physx::BodyType::Dynamic);
}
