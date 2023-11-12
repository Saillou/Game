#include "BaseCommander.hpp"

#include <iostream>

BaseCommander::BaseCommander() {
    // Root events
    _subscribe(&BaseCommander::_on_key_pressed);
}

void BaseCommander::_on_key_pressed(const Event::KeyPressed& evt) {
    std::cout << "BaseCommander::OnKeyPressed: " << evt.key << std::endl;
}