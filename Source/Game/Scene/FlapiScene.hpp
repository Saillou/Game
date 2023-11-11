#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"
#include "../../Engine/Graphic/Shaders/ComputeShader.hpp"
#include "../../Engine/Graphic/Utils/StorageBuffer.hpp"

#include "Objects/Quad.hpp"

struct FlapiScene : public BaseScene {
    FlapiScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    ComputeShader m_physx;
    StorageBuffer<float> m_input;
    StorageBuffer<float> m_output;

    std::unordered_map<std::string, Shader> m_shaders;
    Quad m_shapeGround;
    float m_time;
};