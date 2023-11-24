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
}


// ------------------------ Slime ------------------------
Slime::Slime()
{
    createBody();
}

void Slime::move(glm::vec3& direction) {
    if (!_movePossible)
        return;

    glm::vec3 total = _maxSpeed * direction;
    _pbody->setLinearVelocity(Vector3(total.x, total.y, total.z));
}

void Slime::jump() {
    if (!_jumpPossible)
        return;

    _jumpPossible = false;
    auto time_elapsed = _time.elapsed<Timer::millisecond>();
}

const BaseItem::sBody& Slime::createBody() {
    _body = std::make_shared<SphereBody>(0.10f);
    return _body;
    
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
    player.addTo(scene, Physx::BodyType::Kinematic);
    ennemy.addTo(scene, Physx::BodyType::Static);
    target.addTo(scene, Physx::BodyType::Dynamic);
}
