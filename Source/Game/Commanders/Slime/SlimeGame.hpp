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

    virtual void _onAdd();

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
    float _maxSpeed = 2.0f; // unit/s
    float _accel    = 0.5f; // unit/s^2
    float _jump     = 5.0f; // idk

protected:
    void _onAdd() override;

public:
    Slime();

    void move(glm::vec3& direction);
    void jump();
    void update();

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

    void update();

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
    void update();
};
