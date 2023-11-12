#include "FruitCommander.hpp"

#include <iostream>

FruitCommander::FruitCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<FruitScene>(scene))
{
    // ..
}

// Events
void FruitCommander::_on_key_pressed(const Event::KeyPressed& evt) {
    std::cout << "FruitCommander::OnKeyPressed: " << evt.key << std::endl;

    switch (evt.key) {
        case Key::Space:
            m_scene->test(); 
            break;
    }
    
}
