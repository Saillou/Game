#pragma once

#include "BaseCommander.hpp"
#include "../Scene/FruitScene.hpp"

struct FruitCommander : public BaseCommander {
    FruitCommander(std::shared_ptr<BaseScene> scene);

protected:
    void _on_key_pressed(const Event::KeyPressed& evt) override;
    std::shared_ptr<FruitScene> m_scene;
};