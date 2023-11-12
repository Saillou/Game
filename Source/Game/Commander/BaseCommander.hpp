#pragma once

#include <memory>

#include "../../Engine/Events/Events.hpp"
#include "../../Engine/Graphic/BaseScene.hpp"

// -- Scene --
struct BaseCommander : public Event::Subscriber {
    BaseCommander(std::shared_ptr<BaseScene> scene);
    virtual ~BaseCommander() = default;

protected:
    virtual void _on_key_pressed(const Event::KeyPressed& evt);

    std::shared_ptr<BaseScene> m_scene;
};
