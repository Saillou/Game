#include "Physx.hpp"

#include <iostream>

// Private
Physx& Physx::_get() {
	static Physx physx;
	return physx;
}

// Public
void Physx::Add(std::shared_ptr<BaseBody> body, BodyType type) {
	(type == BodyType::Static ?
		_get().m_static_elements: 
		_get().m_dynamic_elements
	).push_back(body);
}

void Physx::Clear() {
	_get().m_dynamic_elements.clear();
	_get().m_static_elements.clear();
}

void Physx::Compute(float delta_time_ms) {
	Physx& engine(_get());
	
	// Compute bdf for dynamics
	for (auto& body : engine.m_dynamic_elements) {
		if(body->position.z > 0)
			body->position.z -= 0.01f;
	}
}

