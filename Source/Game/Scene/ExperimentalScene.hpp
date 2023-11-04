#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"

#include <memory>
#include <unordered_map>

struct ExperimentalScene : public BaseScene {
    ExperimentalScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    Shader m_shader;

    typedef std::unordered_map<std::string, std::unique_ptr<Shape>> Catalog;
    Catalog m_shapes;
};