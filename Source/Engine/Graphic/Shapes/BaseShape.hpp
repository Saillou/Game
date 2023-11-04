#pragma once

#include <glm/glm.hpp>

#include "../Utils/Array.h"
#include "../Utils/Buffer.h"

#include <vector>
#include <iostream>

class BaseShape
{
public:
	BaseShape();
	virtual ~BaseShape() = default;

	virtual void bind();
	virtual void draw() = 0;

protected:
	virtual void _bindArray();
	virtual void _setAttributes() = 0;

	void _addPoint(float x, float y, float z);
	void _addAsTriangle(unsigned int i0, unsigned int i1, unsigned int i2);
	void _addAsQuad(unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3);

	Array m_vao;
	Buffer m_vbo;
	Buffer m_ebo;

	std::vector<unsigned int> m_indices;
	std::vector<float> m_vertices;
};