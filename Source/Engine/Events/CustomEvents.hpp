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

	// -- Debug --
	struct DebugDrawPoint : public _Base {
		explicit DebugDrawPoint(float x = 0, float y = 0);

		float x;
		float y;
	};
	struct DebugDrawLine : public _Base {
		explicit DebugDrawLine(float x0 = 0, float y0 = 0, float x1 = 0, float y1 = 0);

		float x0;
		float y0;
		float x1;
		float y1;
	};

private:
	enum _Type : int {
		EventKeyPressed,
		EventMouseMoved,

		Debug_Draw_Point,
		Debug_Draw_Line,
	};
};
