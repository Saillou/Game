#pragma once

#include <glm/glm.hpp>
#include "ParallelipipedBody.hpp"
#include "../Objects/Parallelepiped.hpp"

static int parallelipiped_id = 0;

// Shape
struct _ParallelepipedBodyImpl {
	_ParallelepipedBodyImpl(const glm::vec3& position, const glm::vec3& u, const glm::vec3& n, const glm::vec3& w, const glm::vec4& color_) :
		_id(++parallelipiped_id),
		color(color_),
		m_shape(std::make_shared<Parallelepiped>(position, u, n, w))
	{
		m_shape->addRecipe(Cookable::CookType::Solid, color_);
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
	std::shared_ptr<Parallelepiped> m_shape;
};

// Instance
ParallelipipedBody::ParallelipipedBody(const glm::vec3& position_, const glm::vec3& u, const glm::vec3& n, const glm::vec3& w, const glm::vec4& color_) :
	BaseBody(BaseBody::ContactType::Parallelepiped, position_, glm::mat3(u, n, w)),
	vec_direction(u),
	vec_normal(n),
	vec_height(w),
	_impl(new _ParallelepipedBodyImpl(position_, u, n, w, color_))
{
	// .. 
}

ParallelipipedBody::~ParallelipipedBody() {
	delete _impl;
}

// Method
int ParallelipipedBody::id() const {
	return ((_ParallelepipedBodyImpl*)_impl)->id();
}

void ParallelipipedBody::draw(const Camera& camera) const {
	((_ParallelepipedBodyImpl*)_impl)->draw(camera, position);
}