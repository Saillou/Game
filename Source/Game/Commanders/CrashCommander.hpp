#pragma once

#include "../../Engine/Graphic/Base/BaseCommander.hpp"
#include "../Scenes/CrashScene.hpp"
#include "Crash/CrashGame.hpp"

struct CrashCommander : public BaseCommander {
    CrashCommander(std::shared_ptr<BaseScene> scene);

protected:
    // Events
    void _on_game_state_update(const CustomEvents::UpdateGameState& evt) override;
    void _on_key_pressed(const CustomEvents::KeyPressed& evt) override;
    void _on_mouse_moved(const CustomEvents::MouseMoved& evt) override;

private:

    // Members
    std::unique_ptr<CrashGame> m_game;
    std::shared_ptr<CrashScene> m_scene;
};