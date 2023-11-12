#pragma once

#include "BaseCommander.hpp"

struct SlimeCommander : public BaseCommander {
    SlimeCommander() = default;

protected:
    void _on_key_pressed(const Event::KeyPressed& evt) override;
};