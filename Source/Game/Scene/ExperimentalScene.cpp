#include "ExperimentalScene.hpp"

#include <glm/glm.hpp>

ExperimentalScene::ExperimentalScene() : BaseScene() {

}

void ExperimentalScene::resize(int width, int height) {
    // ..
}

void ExperimentalScene::draw() {
    // Background
    glClearColor(0.05f, 0.05f, 0.06f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ..

}
