#include "SlimeObjects.hpp"

using namespace reactphysics3d;


// ------------------------ Player ------------------------
Player::Player()
{
    createBody();
}

void Player::update() {
    if (!_pbody)
        return;

    // Simulate gravity
    {
        constexpr float epsilon = 1e-2f;

        const auto& curr_velocity       = _pbody->getLinearVelocity();
        const auto& curr_transform      = _pbody->getTransform();
        const auto& curr_position       = curr_transform.getPosition();
        const auto& curr_orientation    = curr_transform.getOrientation();

        if (curr_position.z > epsilon) {
            _pbody->setLinearVelocity(curr_velocity - _jump * Vector3(0, 0, 1e-1f));
        }
        else if (curr_position.z != 0.0f) {
            _pbody->setTransform(Transform(Vector3(curr_position.x, curr_position.y, 0.0f), curr_orientation));
        }
    }

    // tunnel
    {
        const auto& curr_velocity       = _pbody->getLinearVelocity();
        const auto& curr_transform      = _pbody->getTransform();
        const auto& curr_position       = curr_transform.getPosition();
        const auto& curr_orientation    = curr_transform.getOrientation();

        if (curr_position.y + curr_velocity.y/60.0f > 1.9f) {
            _pbody->setLinearVelocity(Vector3(curr_velocity.x, 0.0f, curr_velocity.z));
            _pbody->setTransform(Transform(Vector3(curr_position.x, 1.9f, curr_position.z), curr_orientation));
        }

        if (curr_position.y + curr_velocity.y/60.0f < -1.9f) {
            _pbody->setLinearVelocity(Vector3(curr_velocity.x, 0.0f, curr_velocity.z));
            _pbody->setTransform(Transform(Vector3(curr_position.x, -1.9f, curr_position.z), curr_orientation));
        }
    }
}

void Player::move(glm::vec3& direction) {
    if (!_pbody)
        return;

    const auto& curr_transform = _pbody->getTransform();
    const auto& curr_position = curr_transform.getPosition();
    const auto& curr_velocity = _pbody->getLinearVelocity();

    glm::vec3 total = _accel * direction;
    auto new_speed = curr_velocity + Vector3(total.x, total.y, total.z);

    new_speed.x = glm::clamp(new_speed.x, -_maxSpeed, _maxSpeed);
    new_speed.y = glm::clamp(new_speed.y, -_maxSpeed, _maxSpeed);

    // Can't move into the first invisible wall
    if (curr_position.x > 1.9f) {
        if (new_speed.x > 0)
            new_speed.x = 0.0f;
        _pbody->setTransform(Transform(Vector3(1.9f, curr_position.y, curr_position.z), curr_transform.getOrientation()));
    }

    _pbody->setLinearVelocity(new_speed);
}

void Player::jump() {
    if (!_pbody)
        return;

    constexpr float epsilon = 1e-2f;

    if (_pbody->getTransform().getPosition().z > epsilon)
        return;

    auto curr_velocity = _pbody->getLinearVelocity();
    _pbody->setLinearVelocity(curr_velocity + _jump * Vector3(0, 0, 2.0f));
}

const BaseItem::sBody& Player::createBody() {
    _body = std::make_shared<SphereBody>(0.10f);
    return _body;

}

void Player::_onAdd() {
    if (!_pbody)
        return;

    _pbody->setLinearDamping(5.0f);
}



// ------------------------ Ground ------------------------
Ground::Ground(const glm::vec3& dims) :
    m_dims(dims)
{
    createBody();
}

const BaseItem::sBody& Ground::createBody() {
    _body = std::make_shared<BoxBody>(m_dims);
    return _body;
}



// ------------------------ Target ------------------------
Target::Target()
{
    createBody();
}

void Target::update() {
    // Force y-coordinate to 0
    {
        const auto& curr_transform = _pbody->getTransform();
        const auto& curr_position = curr_transform.getPosition();

        if (!enable_3d && curr_position.y != 0.0f) {
            _pbody->setTransform(Transform(
                Vector3(curr_position.x, 0.0f, curr_position.z),
                curr_transform.getOrientation())
            );
        }
    }

    // tunnel
    {
        const auto& curr_velocity = _pbody->getLinearVelocity();
        const auto& curr_transform = _pbody->getTransform();
        const auto& curr_position = curr_transform.getPosition();
        const auto& curr_orientation = curr_transform.getOrientation();

        if (curr_position.y + curr_velocity.y / 60.0f > 1.9f) {
            _pbody->setLinearVelocity(Vector3(curr_velocity.x, 0.0f, curr_velocity.z));
            _pbody->setTransform(Transform(Vector3(curr_position.x, 1.9f, curr_position.z), curr_orientation));
        }

        if (curr_position.y + curr_velocity.y / 60.0f < -1.9f) {
            _pbody->setLinearVelocity(Vector3(curr_velocity.x, 0.0f, curr_velocity.z));
            _pbody->setTransform(Transform(Vector3(curr_position.x, -1.9f, curr_position.z), curr_orientation));
        }
    }
}

const BaseItem::sBody& Target::createBody() {
    _body = std::make_shared<SphereBody>(0.05f);
    return _body;
}




// ------------------------ Ennemy ------------------------
Ennemy::Ennemy(float amplitude, float pulse, float phase, const glm::vec3& dir, const glm::vec3& dims) :
    _dims(dims),
    _moveDirection(dir),
    _amplitude(amplitude),
    _pulse(pulse),
    _phase(phase)
{
    createBody();
}

void Ennemy::update() {
    if (!_pbody)
        return;

    float t = _time.elapsed<Timer::millisecond>() / 1000.0f;
    _pbody->setLinearVelocity
    (
        _amplitude * sin(2 * glm::pi<float>() * _pulse * t + _phase) *
        Vector3(_moveDirection.x, _moveDirection.y, _moveDirection.z)
    );
}

const BaseItem::sBody& Ennemy::createBody() {
    _body = std::make_shared<BoxBody>(_dims);
    return _body;
}