#pragma once

#include "../../Engine/Graphic/Base/BaseCommander.hpp"
#include "../Scene/SlimeScene.hpp"

struct SlimeCommander : public BaseCommander {
    SlimeCommander(std::shared_ptr<BaseScene> scene);

protected:
    void _on_key_pressed(const Event::KeyPressed& evt) override;
    std::shared_ptr<SlimeScene> m_scene;
};