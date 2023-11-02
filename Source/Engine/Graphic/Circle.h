#pragma once

#include "Shape.h"

class Circle : public Shape {
public:
	Circle(float radius);

	void draw() override;

protected:
	void _setAttributes() override;

private:
	float m_radius;
};

