#include "SlimeCommander.hpp"

#include <iostream>

// Events
void SlimeCommander::_on_key_pressed(const Event::KeyPressed& evt) {
    std::cout << "SlimeCommander::OnKeyPressed: " << evt.key << std::endl;
}
