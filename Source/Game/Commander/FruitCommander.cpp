#include "FruitCommander.hpp"

#include "../../Engine/Physx/Physx.hpp"
#include "../../Utils/Timer.hpp"

FruitCommander::FruitCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<FruitScene>(scene))
{    
    // Add first fruit
    m_last_add_ms = Timer::GetCurrentTime<Timer::millisecond>();

    m_scene->addFruit(
        m_currentFruit = std::make_shared<Fruit>(
            0.10f, 
            glm::vec3(0.0f, 0.0f, 1.1f), 
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
        )
    );

    // Data
    const glm::vec4 wallColor(0.3f, 0.7f, 1.0f, 1.0f);
    const glm::vec3 pOrigin(0.f, 0.f, 0.f);

    const float bucketWidth  = 0.50f;
    const float bucketHeight = 0.50f;
    const float bucketDepth  = 0.10f;

    const auto udDirect = bucketWidth  * glm::vec3(1.f, 0.f, 0.f);
    const auto udNormal = bucketDepth  * glm::vec3(0.f, 1.f, 0.f);
    const auto udHeight = bucketHeight * glm::vec3(0.f, 0.f, 1.f);

    // Add walls
    auto ww = m_scene->addWall(std::make_shared<Wall>(pOrigin + (udHeight - udDirect)/2.0f, udNormal, udHeight, wallColor)); // West
    auto we = m_scene->addWall(std::make_shared<Wall>(pOrigin + (udHeight + udDirect)/2.0f, udNormal, udHeight, wallColor)); // East
    auto wb = m_scene->addWall(std::make_shared<Wall>(pOrigin, udDirect, udNormal, wallColor)); // Bottom

    // Physics
    //Physx::Add(ww, Physx::BodyType::Static);
    //Physx::Add(we, Physx::BodyType::Static);
    Physx::Add(wb, Physx::BodyType::Static);
}

// Events
void FruitCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    // Constantes for events
    const int DELAY_MS_ADD = 300; //ms
    const float SPEED_FRUIT = 0.02f;

    // React to the emitted keys 
    if (evt.key == Key::Space) {
        int current_time = Timer::GetCurrentTime<Timer::millisecond>();
        if (current_time - m_last_add_ms > DELAY_MS_ADD) 
        {
            m_last_add_ms = current_time;

            // Use the last fruit position to place the new one
            float last_pos_x = m_currentFruit->position.x;

            // Let fall the current fruit
            Physx::Add(m_currentFruit, Physx::BodyType::Dynamic);

            // .. and add a new
            m_scene->addFruit(
                m_currentFruit = std::make_shared<Fruit>(
                    0.10f,
                    glm::vec3(0.0f, 0.0f, 1.1f),
                    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
                )
            );
            m_currentFruit->position.x = last_pos_x;
        }
    }

    // Move the fruit
    if (evt.key == Key::ArrowLeft) {
        m_currentFruit->position.x += SPEED_FRUIT;
    }

    if (evt.key == Key::ArrowRight) {
        m_currentFruit->position.x -= SPEED_FRUIT;
    }
}
