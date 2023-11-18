#include "Physx.hpp"
#include <glm/gtx/string_cast.hpp>

#include <optional>
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

void Physx::debug2d() {
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

#define WORLD_2D
#ifdef WORLD_2D
static glm::vec3 to3d(const glm::vec2& v) {
	return glm::vec3(-v.x, 0.0f, v.y);
}
static glm::vec2 to2d(const glm::vec3& v) {
	return glm::vec2(-v.x, v.z);
}

void Physx::Compute(float delta_time_ms) {
	Physx& engine(_get());

	// World constantes
	const float dt_sec = delta_time_ms / 1000.0f;
	const glm::vec3 GRAVITY(0.0f, 0.0f, -9.81f);

	//  Dynamic object
	for (auto& body : engine.m_dynamic_elements)
	{
		// Properties
		glm::vec2 body_pos   = to2d(body->position);
		glm::vec2 body_speed = to2d(body->_speedPosition);

		// Bdf
		glm::vec2 accel    = to2d(GRAVITY);
		glm::vec2 speed    = accel * dt_sec + body_speed;
		glm::vec2 position = accel * (dt_sec * dt_sec) / 2.0f + body_speed * dt_sec + body_pos;

		// Static object
		for (const auto& hindrance : engine.m_static_elements)
		{
			if (hindrance->type == BaseBody::ContactType::Parallelepiped) {
				const glm::vec2 line_center = to2d(hindrance->position);
				const glm::vec2 line_dir    = 0.5f*to2d(hindrance->dimensions[0]);
				const glm::vec2 pt_a = line_center - line_dir;
				const glm::vec2 pt_b = line_center + line_dir;
			}
		}

		// Update
		body_pos = position;
		body_speed = speed;

		// To 3D
		body->_speedPosition = to3d(body_speed);
		body->position		 = to3d(body_pos);
	}
}

#else
void Physx::Compute(float delta_time_ms) {
	static bool ignore = false;
	if (ignore)
		return;

	Physx& engine(_get());

	// World constantes
	const float dt_sec = delta_time_ms / 1000.0f;
	const glm::vec3 GRAVITY(0.0f, 0.0f, -9.81f);
	
	// Update positions/velocity
	for (auto& body : engine.m_dynamic_elements) 
	{
		// Bdf
		glm::vec3 accel = GRAVITY;			    
		glm::vec3 speed = accel*dt_sec + body->_speedPosition;
		glm::vec3 position = accel*(dt_sec*dt_sec)/2.0f + body->_speedPosition*dt_sec + body->position;


		// Collisions
		// - Dynamic object variables
		const auto& Pp0 = body->position;
		const auto& Vp0 = body->_speedPosition;

		const auto& Pp1 = position;
		const auto& Vp1 = speed;

		// - Static object variables
		for (const auto& hindrance : engine.m_static_elements) {
			if (hindrance->type != BaseBody::ContactType::Facette) {
				std::cout << "Could not compute collision against a not-facette" << std::endl;
				continue;
			}

			const glm::vec3 Pr = hindrance->position;
			const glm::vec3 Vn = glm::normalize(
				hindrance->dimensions[2] == glm::vec3(0) ? glm::cross(hindrance->dimensions[1], hindrance->dimensions[0]) : hindrance->dimensions[2]
			);

			if (body->type != BaseBody::ContactType::Sphere) {
				std::cout << "Could not compute collision with a not-sphere" << std::endl;
				continue;
			}

			// Boum
			float tc = 0.0f;
			const auto collide_point = ([=](float& r_time_collide) -> std::optional<glm::vec3>
				{
					const float Dp0 = glm::dot(Pp0, Vn);
					const float Dp1 = glm::dot(Pp1, Vn);
					if (Dp0 * Dp1 > 0) // no collision
						return {};

					r_time_collide = std::abs(Dp0) / (std::abs(Dp0) + std::abs(Dp1));
					return r_time_collide * (Pp1-Pp0) + Pp0;
				}
			)(tc);
			if (!collide_point)
				continue; // no boum

			ignore = true;

			// Bounce from collide_point during (1-tc)*dt_sec seconds
			const float dt_c = (1 - tc) * dt_sec;

			speed    = accel*dt_c + body->_speedPosition*(-1.0f); // change sign
			position = accel*(dt_sec*dt_sec)/2.0f + body->_speedPosition * (-1.0f) *dt_sec + collide_point.value();
		}

		// Update
		body->_speedPosition = speed;
		body->position = position;
	}
}
#endif