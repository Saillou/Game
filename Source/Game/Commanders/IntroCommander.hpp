#pragma once

#include "../../Engine/Physx/Physx.hpp"
#include "../../Engine/Graphic/Base/BaseCommander.hpp"
#include "../Scenes/IntroScene.hpp"

struct IntroCommander : public BaseCommander {
    IntroCommander(std::shared_ptr<BaseScene> scene);

protected:
    // Events
    void _on_game_state_update(const CustomEvents::UpdateGameState& evt) override;
    void _on_key_pressed(const CustomEvents::KeyPressed& evt) override;
    void _on_mouse_moved(const CustomEvents::MouseMoved& evt) override;

private:
    // Members
    std::shared_ptr<IntroScene> m_scene;
};