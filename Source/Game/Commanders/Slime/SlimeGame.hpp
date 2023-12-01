#pragma once

#include <glm/gtx/string_cast.hpp>

#include "SlimeObjects.hpp"
#include "../Common/BaseItem.hpp"
#include "../../Scenes/SlimeScene.hpp"
#include "../../../Engine/Physx/Physx.hpp"
#include "../../../Utils/Timer.hpp"

// ------------ Members ------------
struct SlimeGame
{
    // Data
    const float IntroDuration   = 2.0f; // s
    const float Game2DLimit     = -4.0f;    // vp unit
    const float Game3DLimit     = -15.0f;

    // Variables
    enum State {
        None,
        Intro,
        Game2D,
        Game3D,
        BossIntro,
        BossFight,
        End
    } state = State::None;

    Player player;
    Target target;

    std::vector<Ennemy> ennemies;
    std::vector<Ground> groundMeshes;
    std::vector<Ground> invisbleWalls;

    std::shared_ptr<SlimeScene> scene;

    float last_state_change = 0.0f;

    // Methods
    SlimeGame();

    void useScene(std::shared_ptr<SlimeScene> scene);
    void update(float time_sec, State desired_state);

private:
    void _change_state(State new_state);

    void _update_intro(float time_sec);
    void _update_game2d(float time_sec);
    void _update_game3d(float time_sec);
    void _update_bossIntro(float time_sec);
    void _update_bossFight(float time_sec);

};
