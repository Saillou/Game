#pragma once

#include <glm/gtx/string_cast.hpp>

#include "../Common/BaseItem.hpp"
#include "../../Scenes/SlimeScene.hpp"
#include "../../../Engine/Physx/Physx.hpp"
#include "../../../Utils/Timer.hpp"

// ------------ Slime ------------
class Player : public BaseItem {
    float _maxSpeed = 2.0f; // unit/s
    float _accel = 0.2f; // unit/s^2
    float _jump = 5.0f; // idk

protected:
    void _onAdd() override;

public:
    Player();

    void move(glm::vec3& direction);
    void jump();
    void update();

    const sBody& createBody() override;
};

// ------------ Ground ------------
struct Ground : public BaseItem {
    Ground(const glm::vec3& dims);

    const sBody& createBody() override;

private:
    glm::vec3 m_dims;
};

// ------------ Target ------------
struct Target : public BaseItem {
    Target();

    void update();
    void manual_update();

    const sBody& createBody() override;

public:
    bool enable_3d = false;
};

// ------------ Ennemy ------------
struct Ennemy : public BaseItem {
    Ennemy(float amplitude, float pulse, float phase, const glm::vec3& dir, const glm::vec3& dims);

    void update();

    const sBody& createBody() override;

private:
    glm::vec3 _dims;
    glm::vec3 _moveDirection;
    float _amplitude;
    float _pulse;
    float _phase;
};
