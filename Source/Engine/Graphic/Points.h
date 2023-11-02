#pragma once

#include "Shape.h"

#include <vector>

class Points : public Shape {
public:
	struct Data {
		struct Position {
			float x;
			float y;
		} position;

		struct Color {
			float r;
			float g;
			float b;
		} color;
	};

	Points(const std::vector<Data>& points);
	void draw() override;

protected:
	void _setAttributes() override;
};

