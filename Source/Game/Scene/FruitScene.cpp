#include "FruitScene.hpp"

#include <algorithm>
#include <random>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

// Scene instance
FruitScene::FruitScene() :
    BaseScene()
{

}

void FruitScene::resize(int width, int height) {
    // ..
}

void FruitScene::draw() {


    // Draw texts
    TextEngine::Write("Fruits", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}
