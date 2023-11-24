#pragma once

#include "../../Engine/Graphic/Base/BaseCommander.hpp"
#include "../Scenes/SlimeScene.hpp"
#include "Slime/SlimeGame.hpp"

struct SlimeCommander : public BaseCommander {
    SlimeCommander(std::shared_ptr<BaseScene> scene);

protected:
    // Events
    void _on_key_pressed(const CustomEvents::KeyPressed& evt) override;
    void _on_mouse_moved(const CustomEvents::MouseMoved& evt) override;

private:

    // Members
    std::unique_ptr<SlimeGame> m_game;
    std::shared_ptr<SlimeScene> m_scene;
};