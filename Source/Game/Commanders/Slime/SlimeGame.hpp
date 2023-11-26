#pragma once


#include <glm/gtx/string_cast.hpp>

#include "../Common/BaseItem.hpp"
#include "../../Scenes/SlimeScene.hpp"
#include "../../../Engine/Physx/Physx.hpp"
#include "../../../Utils/Timer.hpp"

// ------------ Members ------------
struct SlimeGame
{
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

    // ------------ Members ------------
    Slime  player;
    Slime  ennemy;
    Ground ground;
    Target target;
    std::shared_ptr<SlimeScene> scene;

    SlimeGame();

    void useScene(std::shared_ptr<SlimeScene> scene);
    void update(float time_sec, SlimeScene::State desired_state);
};
