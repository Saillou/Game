#pragma once

#include "Events.hpp"

// Define events available
struct CustomEvents : public Event {
	// -- Keyboard --
	struct KeyPressed : public _Base {
		explicit KeyPressed(int key = -1);
		int key;
	};

	// -- Mouse --
	struct MouseMoved : public _Base {
		explicit MouseMoved(int x = 0, int y = 0);
		int x;
		int y;
	};

private:
	enum _Type : int {
		EventKeyPressed,
		EventMouseMoved
	};
};
