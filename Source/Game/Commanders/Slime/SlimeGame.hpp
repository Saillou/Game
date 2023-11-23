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
    glm::vec3           _position;
    sBody               _body;

public:
    explicit BaseItem(const glm::vec3& initial_position = glm::vec3(0, 0, 0));
    virtual ~BaseItem() = default;

    // Getters
    const glm::vec3& position() const;
    const sBody& body() const;

    // Methods
    void addTo(std::shared_ptr<SlimeScene> scene);

private:
    virtual const sBody& createBody() = 0;
};

// ------------ Slime ------------
class Slime : public BaseItem {
    bool _jumpPossible = true;
    bool _movePossible = true;

public:
    Slime();

    void move(glm::vec3& direction, float distance = 1.0f);
    void jump();

    const sBody& createBody() override;
};

// ------------ Ground ------------
struct Ground : public BaseItem {
    Ground();

    const glm::vec3 normal = glm::vec3(0, 0, 1);

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
    Slime  opponent;
    Ground ground;
    Target target;

    SlimeGame() = default;
    ~SlimeGame() = default;

    void useScene(std::shared_ptr<SlimeScene> scene);
};
