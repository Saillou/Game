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


// -- Debug events --
CustomEvents::DebugDrawPoint::DebugDrawPoint(float x, float y) :
	_Base(_Type::Debug_Draw_Point),
	x(x), y(y)
{
	// ..
}

CustomEvents::DebugDrawLine::DebugDrawLine(float x0, float y0, float x1, float y1) :
	_Base(_Type::Debug_Draw_Line),
	x0(x0), y0(y0),
	x1(x1), y1(y1)
{
	// ..
}

