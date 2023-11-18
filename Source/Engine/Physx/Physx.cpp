#include "Physx.hpp"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>

#include <optional>
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
	).insert(body);
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

	//  Dynamic objects
	for (auto& body : engine.m_dynamic_elements)
	{
		// Properties - Dynamic
		glm::vec2 body_pos   = to2d(body->position);
		glm::vec2 body_speed = to2d(body->_speedPosition);

		// Bdf
		glm::vec2 accel    = to2d(GRAVITY);
		glm::vec2 speed    = accel * dt_sec + body_speed;
		glm::vec2 position = accel * (dt_sec * dt_sec) / 2.0f + body_speed * dt_sec + body_pos;

		// Static objects
		for (const auto& hindrance : engine.m_static_elements)
		{
			// Properties - Static
			const glm::vec2 hind_center				   = to2d(hindrance->position);
			std::optional<glm::vec2> collide_direction = {};

			switch (body->type)
			{
			case BaseBody::ContactType::Sphere:
			{
				// Collide
				float body_radius = body->dimensions[0][0];

				switch (hindrance->type)
				{
					// ---- Contact Sphere / Parallelepiped ----
				case BaseBody::ContactType::Parallelepiped:
				{
					const glm::vec2 line_dir = to2d(hindrance->dimensions[0]);
					const glm::vec2 pt_a = hind_center - line_dir;
					const glm::vec2 pt_b = hind_center + line_dir;

					if (glm::dot(position - pt_a, line_dir) * glm::dot(position - pt_b, line_dir) < 0) {
						float dist_line =
							std::abs((pt_b.x - pt_a.x) * (pt_a.y - position.y) - (pt_a.x - position.x) * (pt_b.y - pt_a.y)) /
							glm::distance(pt_a, pt_b);

						if (dist_line < body_radius) {
							collide_direction = glm::normalize(glm::vec2(-line_dir.y, line_dir.x));
						}
					}

					else if (glm::distance(pt_a, position) < body_radius) {
						collide_direction = glm::normalize(pt_a - position);
					}

					else if (glm::distance(pt_b, position) < body_radius) {
						collide_direction = glm::normalize(pt_b - position);
					}
				} break;

				// -- Contact Sphere / Sphere
				case BaseBody::ContactType::Sphere:
				{
					float hind_radius = hindrance->dimensions[0][0];

					// Collide
					float d = glm::distance(position, hind_center);
					if (d > hind_radius + body_radius)
						continue; // No boum

					// Collide point
					collide_direction = glm::normalize(hind_center - position);
				} break;
				}

				// no boum
				if (!collide_direction.has_value())
					continue;

				glm::vec2 collide_point = position + body_radius * collide_direction.value();
				std::cout << glm::to_string(position) << " " << glm::to_string(collide_point) << std::endl;

			} break; // End contact sphere
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