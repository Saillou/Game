#include "SlimeGame.hpp"

// ------------ Base ------------
BaseItem::BaseItem(const glm::vec3& initial_position):
    _position(initial_position),
    _body(nullptr)
{ }

// Getters
const glm::vec3& BaseItem::position() const {
    return _position;
}
const BaseItem::sBody& BaseItem::body() const {
    return _body;
}

// Methods
void BaseItem::addTo(std::shared_ptr<SlimeScene> scene) {
    scene->add(_body ? _body : createBody());
}


// ------------ Slime ------------
Slime::Slime()
{
    createBody();
}

void Slime::move(glm::vec3& direction, float distance) {
    if (!_movePossible)
        return;

    _movePossible = false;
    auto time_elapsed = _time.elapsed<Timer::millisecond>();
}

void Slime::jump() {
    if (!_jumpPossible)
        return;

    _jumpPossible = false;
    auto time_elapsed = _time.elapsed<Timer::millisecond>();
}

const BaseItem::sBody& Slime::createBody() {
    _body = std::make_shared<SphereBody>(0.10f);
    Physx::Add(_body);

    return _body;
    
}

// ------------ Ground ------------
Ground::Ground()
{
    createBody();
}

const BaseItem::sBody& Ground::createBody() {
    constexpr float infinity(1.0f);

    _body = std::make_shared<BoxBody>(glm::vec3(2.0f * infinity, 2.0f * infinity, 4.0f / (infinity* infinity))); // i love pissing of mathematician lol
    Physx::Add(_body);
    
    return _body;
}

// ------------ Target ------------
Target::Target()
{
    createBody();
}

const BaseItem::sBody& Target::createBody() {
    _body = std::make_shared<SphereBody>(0.05f);
    Physx::Add(_body);

    return _body;
}

// ------------ Implementation ------------
void SlimeGame::useScene(std::shared_ptr<SlimeScene> scene) {
    ground.addTo(scene);
    player.addTo(scene);
    opponent.addTo(scene);
    target.addTo(scene);
}
