#pragma once

#include "../../Engine/Physx/Physx.hpp"
#include "../../Engine/Graphic/Base/BaseCommander.hpp"
#include "../Scenes/SlimeScene.hpp"

struct SlimeCommander : public BaseCommander {
    SlimeCommander(std::shared_ptr<BaseScene> scene);

protected:
    // Events
    void _on_key_pressed(const CustomEvents::KeyPressed& evt) override;
    void _on_mouse_moved(const CustomEvents::MouseMoved& evt) override;

private:
    // Members
    std::shared_ptr<SlimeScene> m_scene;
};