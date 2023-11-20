#pragma once

#include <glm/glm.hpp>

// Objects
struct Light {
	Light(const glm::vec3& position, const glm::vec4& color);

private:
	glm::vec3 m_position;
	glm::vec4 m_color;
};
