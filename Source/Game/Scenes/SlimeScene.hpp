#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

#include <unordered_map>
#include <vector>

#include "Bodies/BoxBody.hpp"
#include "Bodies/SphereBody.hpp"

// -- Scene --
struct SlimeScene : public BaseScene {
    SlimeScene();

    void draw() override;
    void resize(int width, int height) override;

    void add(const std::shared_ptr<BaseBody>& body);

private:
    std::vector<std::shared_ptr<BaseBody>> _baseBodies;

    void _camera_update();
};
