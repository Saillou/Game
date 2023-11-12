#pragma once

#include "../../Engine/Events/Events.hpp"

// -- Scene --
struct BaseCommander : public Event::Subscriber {
    BaseCommander();
    virtual ~BaseCommander() = default;

protected:
    virtual void _on_key_pressed(const Event::KeyPressed& evt);
};
