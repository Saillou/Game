#pragma once

#include <glm/glm.hpp>
#include "FacetteBody.hpp"
#include "../Objects/Facette.hpp"

static int facette_id = 0;

// Shape
struct _FacetteBodyImpl {
	_FacetteBodyImpl(const glm::vec3& position, const glm::vec3& u, const glm::vec3& n, const glm::vec4& color_) :
		_id(++facette_id),
		color(color_),
		m_shape(std::make_shared<Facette>(position, u, n))
	{
		m_shape->addRecipe(Facette::CookType::Solid, color_);
	}

	void draw(const Camera& camera, const glm::vec3& position) {
		m_shape->draw(camera, position);
	}

	int id() const {
		return _id;
	}

private:
	int _id;
	glm::vec4 color;
	std::shared_ptr<Facette> m_shape;
};

// Instance
FacetteBody::FacetteBody(const glm::vec3& position_, const glm::vec3& u, const glm::vec3& n, const glm::vec4& color_) :
	BaseBody(position_),
	vec_direction(u),
	vec_normal(n),
	_speedPosition(glm::vec3()),
	_impl(new _FacetteBodyImpl(position_, u, n, color_))
{
	// .. 
}

FacetteBody::~FacetteBody() {
	delete _impl;
}

// Method
int FacetteBody::id() const {
	return ((_FacetteBodyImpl*)_impl)->id();
}

void FacetteBody::draw(const Camera& camera) const {
	((_FacetteBodyImpl*)_impl)->draw(camera, position);
}