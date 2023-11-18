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

// -- Mouse events --
Event::MouseMoved::MouseMoved(int x, int y) :
	_Base(_Type::MouseMoved),
	x(x), y(y)
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
