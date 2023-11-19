#include "BaseScene.hpp"

#include <glad/glad.h>

BaseScene::BaseScene() {
    _init_gl_config();
}

BaseScene::~BaseScene() {
}

void BaseScene::moveCameraPosition(float dx, float dy, float dz) {
    m_camera.position.x += dx;
    m_camera.position.y += dy;
    m_camera.position.z += dz;
}
void BaseScene::moveCameraDirection(float dx, float dy, float dz) {
    m_camera.direction.x += dx;
    m_camera.direction.y += dy;
    m_camera.direction.z += dz;
}
void BaseScene::changeCameraPerspective(float dfov) {
    m_camera.fieldOfView += dfov;
}

void BaseScene::draw() {
    // to be overrided
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

int BaseScene::width() const {
    return m_width;
}
int BaseScene::height() const {
    return m_height;
}