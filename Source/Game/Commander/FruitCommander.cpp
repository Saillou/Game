#include "FruitCommander.hpp"

#include "../../Utils/Timer.hpp"

FruitCommander::FruitCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<FruitScene>(scene))
{
    m_last_add_ms = Timer::GetCurrentTime<Timer::millisecond>();
}

// Events
void FruitCommander::_on_key_pressed(const Event::KeyPressed& evt) {
    if (evt.key == Key::Space) {
        const int DELAY_MS_ADD = 300; //ms
        int current_time = Timer::GetCurrentTime<Timer::millisecond>();
        
        if (current_time - m_last_add_ms > DELAY_MS_ADD) {
            m_last_add_ms = current_time;
            m_scene->addFruit(std::make_shared<Fruit>(0.10f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
        }
    }
}
