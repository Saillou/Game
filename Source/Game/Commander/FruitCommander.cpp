#include "FruitCommander.hpp"

#include "../../Utils/Timer.hpp"

FruitCommander::FruitCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<FruitScene>(scene))
{
    // Reset timer
    m_last_add_ms = Timer::GetCurrentTime<Timer::millisecond>();

    // Data
    const glm::vec4 wallColor(0.3f, 0.7f, 1.0f, 1.0f);

    const glm::vec3 pOrigin(0.f, 0.f, 0.f);

    const glm::vec3 uDirect(1.f, 0.f, 0.f);
    const glm::vec3 uNormal(0.f, 1.f, 0.f);
    const glm::vec3 uHeight(0.f, 0.f, 1.f);

    const float cst_plank = 1e-3f;
    const float infinity = 1e+1f;

    const float bucketWidth = 0.50f;
    const float bucketHeight = 0.50f;
    const float bucketDepth = 0.10f;

    const auto udDirect = bucketWidth  * uDirect;
    const auto udNormal = bucketDepth  * uNormal;
    const auto udHeight = bucketHeight * uHeight;

    // Add walls
    m_scene->addWall(std::make_shared<Wall>(pOrigin - udDirect + udHeight, udNormal, udHeight, wallColor)); // West
    m_scene->addWall(std::make_shared<Wall>(pOrigin + udDirect + udHeight, udNormal, udHeight, wallColor)); // East
    m_scene->addWall(std::make_shared<Wall>(pOrigin, udDirect, udNormal, wallColor)); // Bottom
}

// Events
void FruitCommander::_on_key_pressed(const Event::KeyPressed& evt) {
    if (evt.key == Key::Space) {
        // Add fruits
        const int DELAY_MS_ADD = 300; //ms
        int current_time = Timer::GetCurrentTime<Timer::millisecond>();
        
        if (current_time - m_last_add_ms > DELAY_MS_ADD) {
            m_last_add_ms = current_time;
            m_scene->addFruit(std::make_shared<Fruit>(0.10f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
        }
    }
}
