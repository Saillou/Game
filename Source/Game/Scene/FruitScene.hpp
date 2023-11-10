#pragma once

#include "../../Utils/Caster.hpp"
#include "../../Engine/Graphic/Camera.hpp"
#include "../../Engine/Graphic/BaseScene.hpp"
#include "../../Engine/Graphic/Drawables/BaseShape.hpp"
#include "../../Engine/Graphic/Shaders/ComputeShader.hpp"
#include "../../Engine/Graphic/Utils/StorageBuffer.hpp"

#include <unordered_map>
#include <memory>

// -- Scene --
struct FruitScene : public BaseScene {
    FruitScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    std::unordered_map<std::string, sObject> m_shapes;
    Camera m_camera;
};
