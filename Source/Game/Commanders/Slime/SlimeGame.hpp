#pragma once


#include <glm/gtx/string_cast.hpp>

#include "../../Scenes/SlimeScene.hpp"
#include "../../../Engine/Physx/Physx.hpp"
#include "../../../Utils/Timer.hpp"

// ------------ Base ------------
class BaseItem {
protected:
    using sBody = std::shared_ptr<BaseBody>;

    Timer::Chronometre  _time;
    sBody               _body;
    Physx::PBody        _pbody;

public:
    explicit BaseItem();
    virtual ~BaseItem() = default;

    // Getters
    sBody body() const;

    // Methods
    void addTo(std::shared_ptr<SlimeScene> scene, Physx::BodyType type);

private:
    virtual const sBody& createBody() = 0;
};

// ------------ Slime ------------
class Slime : public BaseItem {
    bool _jumpPossible = true;
    bool _movePossible = true;
    float _maxSpeed = 10.0f; // unit/s

public:
    Slime();

    void move(glm::vec3& direction);
    void jump();

    const sBody& createBody() override;
};

// ------------ Ground ------------
struct Ground : public BaseItem {
    Ground();

    const sBody& createBody() override;
};

// ------------ Target ------------
struct Target : public BaseItem {
    Target();

    const sBody& createBody() override;
};

// ------------ Implementation ------------
struct SlimeGame
{
    Slime  player;
    Slime  ennemy;
    Ground ground;
    Target target;

    SlimeGame();

    void useScene(std::shared_ptr<SlimeScene> scene);
};
