#pragma once

#include "BoxBody.hpp"
#include "../Objects/Box.hpp"

static int parallelipiped_id = 0;

// Shape
struct _BoxBodyImpl {
	_BoxBodyImpl(const glm::vec3& dimensions, const glm::vec4& color_) :
		_id(++parallelipiped_id),
		color(color_),
		m_shape(std::make_shared<Box>(dimensions))
	{
		m_shape->addRecipe(Cookable::CookType::Solid, color_);
	}

	void draw(const Camera& camera, const glm::vec3& position, const glm::vec3& orientation, const std::vector<std::unique_ptr<Light>>& lights) {
		m_shape->draw(camera, position, orientation, lights);
	}

	int id() const {
		return _id;
	}

private:
	int _id;
	glm::vec4 color;
	std::shared_ptr<Box> m_shape;
};

// Instance
BoxBody::BoxBody(const glm::vec3& dimensions, const glm::vec4& color_) :
	BaseBody(BaseBody::ContactType::Box, glm::vec3(0.0f), dimensions),
	dimensions(dimensions),
	_impl(new _BoxBodyImpl(dimensions, color_))
{
	// .. 
}

BoxBody::~BoxBody() {
	delete _impl;
}

// Method
int BoxBody::id() const {
	return ((_BoxBodyImpl*)_impl)->id();
}

void BoxBody::draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights) const {
	((_BoxBodyImpl*)_impl)->draw(camera, position, orientation, lights);
}