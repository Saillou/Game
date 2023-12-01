#pragma once

#include <memory>

#include "BaseScene.hpp"
#include "../../Events/CustomEvents.hpp"

// -- Scene --
struct BaseCommander : public Event::Subscriber {
    BaseCommander(std::shared_ptr<BaseScene> scene);
    virtual ~BaseCommander() = default;

protected:
    virtual void _on_game_state_update(const CustomEvents::UpdateGameState& evt);
    virtual void _on_key_pressed(const CustomEvents::KeyPressed& evt);
    virtual void _on_mouse_moved(const CustomEvents::MouseMoved& evt);

    std::shared_ptr<BaseScene> m_scene;
};
