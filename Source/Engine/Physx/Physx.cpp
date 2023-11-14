#include "Physx.hpp"

#include <glm/gtx/string_cast.hpp>

#include <iostream>

// ----- D e b u g -----
void Physx::debug() {
	Physx& engine = _get();

	std::cout << "m_dynamic_elements: " << engine.m_dynamic_elements.size() << std::endl;
	for (auto& body : engine.m_dynamic_elements) {
		std::cout << " - Type: " << (int)body->type << std::endl;
		std::cout << " - Position: " << glm::to_string(body->position) << std::endl;
		std::cout << " - Dimensions: " << glm::to_string(body->dimensions) << std::endl;
		std::cout << " - Orientation: " << glm::to_string(body->orientation) << std::endl;
		std::cout << std::endl;
	}

	std::cout << "m_static_elements: " << engine.m_static_elements.size() << std::endl;
	for (auto& body : engine.m_static_elements) {
		std::cout << " - Type: " << (int)body->type << std::endl;
		std::cout << " - Position: " << glm::to_string(body->position) << std::endl;
		std::cout << " - Dimensions: " << glm::to_string(body->dimensions) << std::endl;
		std::cout << " - Orientation: " << glm::to_string(body->orientation) << std::endl;
		std::cout << std::endl;
	}
}

// ------------------------

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
		static bool once = false;
		if (!once) {
			once = true;
			debug();
		}
		if(body->position.z > 0)
			body->position.z -= 0.01f;
	}
}

