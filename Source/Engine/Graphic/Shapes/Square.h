#pragma once

#include "Shape.h"

class Square : public Shape {
public:
	Square(float side);

	void draw() override;

protected:
	void _setAttributes() override;

private:
	float m_side;
};

