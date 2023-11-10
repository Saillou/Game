#include "ExperimentalScene.hpp"

#include <sstream>
#include <vector>
#include <unordered_map>
#include <utility>

#include "Objects/Rectangle.hpp"
#include "Objects/Ellipse.hpp"

// Scene instance
ExperimentalScene::ExperimentalScene() : BaseScene() {
    // ..
}

void ExperimentalScene::resize(int width, int height) {
    // ..
}

void ExperimentalScene::draw() {
    // Draw damier
    const int N = 20;
    const int N_2 = N*N;

    const glm::vec4 COLOR_1 = glm::vec4(0x1E, 0x1E, 0x1E, 0xFF) / 255.0f;
    const glm::vec4 COLOR_2 = glm::vec4(0x69, 0x69, 0x69, 0xFF) / 255.0f;

    for (int x = -N; x < N; x++) {
        for (int y = -N; y < N; y++) {
            const glm::vec3 POS   = glm::vec3(x, y, 0.f) / (float)N;
            const glm::vec2 SIZE  = glm::vec2(1, 1)      / (float)N;
            const glm::vec4 COLOR = std::abs(x + y) % 2 ? COLOR_1 : COLOR_2;
            const float alpha = (N_2 - x*x) * (N_2 - y*y) / float(N_2*N_2);

            Rectangle::Draw(POS, SIZE, alpha*COLOR);
        }
    }

    // Draw half-ellipse
    Ellipse::Draw(
        glm::vec3(-0.5f, -0.5f, -0.25f),
        glm::vec2(0.40f, 0.30f),
        glm::vec2(0.0f, glm::pi<float>()),
        glm::vec4(1.0f, 0.5f, 0.2f, 1.0f)
    );

    // Circle
    Ellipse::Draw(
        glm::vec3(0.0f, 0.0f, -0.40f),
        glm::vec2(0.10f, 0.10f),
        glm::vec2(0.0f, 2.0f*glm::pi<float>()),
        glm::vec4(0.4f, 0.7f, 0.2f, 1.0f)
    );

    // Draw texts
    TextEngine::Write("Experimental scene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}
