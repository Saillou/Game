#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Utils/Array.hpp"
#include "Utils/Buffer.hpp"

#include <vector>

class BaseShape
{
public:
	BaseShape();
	virtual ~BaseShape() = default;

	virtual void bind();
	virtual void draw() = 0;

	int indicesLength() const;
	int verticesLength() const;

protected:
	virtual void _bindArray();
	virtual void _setAttributes() = 0;

	void _addPoint(float x, float y, float z);
	void _addPoint(const glm::vec3& vec);

	void _addAsLine(unsigned int i0, unsigned int i1);
	void _addAsTriangle(unsigned int i0, unsigned int i1, unsigned int i2);
	void _addAsQuad(unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3);

	Array m_vao;
	Buffer m_vbo;
	Buffer m_ebo;

	std::vector<unsigned int> m_indices;
	std::vector<float> m_vertices;
};
