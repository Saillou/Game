#pragma once

#include <glm/glm.hpp>
#include "SphereBody.hpp"
#include "../Objects/Sphere.hpp"

static int sphere_id = 0;

// Shape
struct _SphereBodyImpl {
	_SphereBodyImpl(float radius_, const glm::vec4& color_) :
		_id(++sphere_id),
		color(color_),
		m_shape(std::make_shared<Sphere>(glm::vec3(0.f), radius_))
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
	std::shared_ptr<Sphere> m_shape;
};

// Instance
SphereBody::SphereBody(float radius_, const glm::vec4& color_) :
	BaseBody(BaseBody::ContactType::Sphere, glm::vec3(0.0f), glm::vec3(radius_, radius_, radius_)),
	radius(radius_),
	_impl(new _SphereBodyImpl(radius_, color_))
{
	// ..
}

SphereBody::~SphereBody() {
	delete _impl;
}

// Method
int SphereBody::id() const {
	return ((_SphereBodyImpl*)_impl)->id();
}

void SphereBody::draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights) const {
	((_SphereBodyImpl*)_impl)->draw(camera, position, orientation, lights);
}