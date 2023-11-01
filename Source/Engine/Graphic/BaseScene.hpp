#pragma once

struct BaseScene {
    BaseScene();
    virtual ~BaseScene();

    virtual void draw() = 0;

protected:
    virtual void _init_gl_config();
};
