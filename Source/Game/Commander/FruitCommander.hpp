#pragma once

#include "BaseCommander.hpp"

struct FruitCommander : public BaseCommander {
    FruitCommander() = default;

protected:
    void _on_key_pressed(const Event::KeyPressed& evt) override;
};