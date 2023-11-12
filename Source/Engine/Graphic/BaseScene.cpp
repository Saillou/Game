#include "BaseScene.hpp"

#include <glad/glad.h>

BaseScene::BaseScene() {
    _init_gl_config();

    // Root events
    _subscribe(&BaseScene::_on_key_pressed);
}

BaseScene::~BaseScene() {
}

void BaseScene::resize(int width, int height) {
    m_width = width;
    m_height = height;
}

void BaseScene::_init_gl_config() {
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void BaseScene::_on_key_pressed(const Event::KeyPressed& evt) {
    std::cout << "BaseScene::OnKeyPressed: " << evt.key << std::endl;
}
