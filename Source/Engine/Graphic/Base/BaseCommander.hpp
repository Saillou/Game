#pragma once

#include <memory>

#include "BaseScene.hpp"
#include "../../Events/Events.hpp"

// -- Scene --
struct BaseCommander : public Event::Subscriber {
    BaseCommander(std::shared_ptr<BaseScene> scene);
    virtual ~BaseCommander() = default;

protected:
    virtual void _on_key_pressed(const Event::KeyPressed& evt);
    virtual void _on_mouse_moved(const Event::MouseMoved& evt);

    std::shared_ptr<BaseScene> m_scene;
};
