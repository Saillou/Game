#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

#include <unordered_map>
#include <vector>

#include "Bodies/BoxBody.hpp"
#include "Bodies/SphereBody.hpp"

// -- Scene --
struct SlimeScene : public BaseScene {
    enum State {
        None,
        Intro,
        Game2D,
        Game3D,
        Game4D,
        Ending
    };

    SlimeScene();

    void draw() override;
    void resize(int width, int height) override;

    void add(const std::shared_ptr<BaseBody>& body);
    void lightning(bool enable);

    bool enable_2d_camera = true;
    State state = None;

    // Data
    static const std::unordered_map<SlimeScene::State, float> StartTime;

private:
    std::vector<std::shared_ptr<BaseBody>> _baseBodies;
    void _camera_update();
};
