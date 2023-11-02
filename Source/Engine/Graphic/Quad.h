#pragma once

#include "Shape.h"

struct Quad : public Shape {
    Quad();
    void draw() override;

protected:
    void _setAttributes() override;
};