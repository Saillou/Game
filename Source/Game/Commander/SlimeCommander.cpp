#include "SlimeCommander.hpp"

#include <iostream>

SlimeCommander::SlimeCommander(std::shared_ptr<BaseScene> scene) :
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<SlimeScene>(scene))
{

}

// Events
//void SlimeCommander::_on_key_pressed(const Event::KeyPressed& evt) {
//    std::cout << "SlimeCommander::OnKeyPressed: " << evt.key << std::endl;
//}
