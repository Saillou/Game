#include "BaseScene.hpp"

#include <glad/glad.h>

BaseScene::BaseScene() {
    _init_gl_config();
}

BaseScene::~BaseScene() {
}

void BaseScene::resize(int width, int height) {
    // to be overrided
}

void BaseScene::_init_gl_config() {
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}