#pragma once

#include "Shape.h"

class Icosahedron : public Shape {
public:
	Icosahedron();

	void draw() override;

protected:
	void _setAttributes() override;

};

