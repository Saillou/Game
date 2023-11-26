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

// -- Game events --
CustomEvents::UpdateGameState::UpdateGameState() :
	_Base(_Type::EventUpdateGameState)
{
	// ..
}

CustomEvents::SceneEnded::SceneEnded() :
	_Base(_Type::EventSceneEnded)
{
	// ..
}

CustomEvents::SceneRefresh::SceneRefresh() :
	_Base(_Type::EventSceneRefresh)
{
	// ..
}
