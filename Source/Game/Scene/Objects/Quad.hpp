#pragma once

#include "../../../Engine/Graphic/Drawables/BaseShape.hpp"

struct Quad : public BaseShape {
    Quad();
    void draw() override;

protected:
    void _setAttributes() override;
};