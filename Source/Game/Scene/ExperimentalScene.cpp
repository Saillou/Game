#include "ExperimentalScene.hpp"

#include <sstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <glm/glm.hpp>

// Scene instance
ExperimentalScene::ExperimentalScene() : BaseScene() {
    // ..
}

void ExperimentalScene::resize(int width, int height) {
    // ..
}

void ExperimentalScene::draw() {
    // Background
    glClearColor(0.05f, 0.05f, 0.06f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw shapes
    const int N = 5;
    const glm::vec4 COLOR_1 = glm::vec4(0x1E, 0x1E, 0x1E, 0xFF) / 255.0f;
    const glm::vec4 COLOR_2 = glm::vec4(0x49, 0x49, 0x49, 0xFF) / 255.0f;

    for (int x = -N; x < N; x++) {
        for (int y = -N; y < N; y++) {
            const glm::vec2 POS   = glm::vec2(x, y) / (float)N;
            const glm::vec2 SIZE  = glm::vec2(1, 1) / (float)N;
            const glm::vec4 COLOR = (x + y) % 2 ? COLOR_1 : COLOR_2;

            Rectangle::Draw(POS, SIZE, COLOR);
        }
    }

    // Draw texts
    TextEngine::Write("Yo world!", 10.0f, 10.0f, 0.5f, glm::vec3(0.7f, 0.7f, 0.7f));
}
