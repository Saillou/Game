#include "Events.hpp"

#include <iostream>

// Static
std::unordered_set<Event::Subscriber*> Event::_allSubscribers;

// Public
// -- Keyboard events --
Event::KeyPressed::KeyPressed(int key) :
	_Base(_Type::KeyPressed),
	key(key) 
{
	// ..
}

// Private
Event::Subscriber::Subscriber() {
	_allSubscribers.insert(this);
}

Event::Subscriber::~Subscriber() {
	_allSubscribers.erase(this);
}
