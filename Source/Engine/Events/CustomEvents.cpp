#include "CustomEvents.hpp"

// Public
// -- Keyboard events --
CustomEvents::KeyPressed::KeyPressed(int key) :
	_Base(_Type::EventKeyPressed),
	key(key)
{
	// ..
}

// -- Mouse events --
CustomEvents::MouseMoved::MouseMoved(int x, int y) :
	_Base(_Type::EventMouseMoved),
	x(x), y(y)
{
	// ..
}