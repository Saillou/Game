#include "Physx.hpp"
#include "../Events/CustomEvents.hpp"

#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>

#include <optional>
#include <iostream>

using namespace glm;

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

void Physx::Compute(float delta_time_ms) {
	Physx& engine(_get());

	// Helper
	static const auto to3d = [=](const vec2& v) -> vec3 {
		return vec3(-v.x, 0.0f, v.y);
	};
	static const auto to2d = [=](const vec3& v) -> vec2 {
		return vec2(-v.x, v.z);
	};

	// World constantes
	const float dt_sec = delta_time_ms / 1000.0f;
	const vec3 GRAVITY(0.0f, 0.0f, -1.0f);

	//  Dynamic objects
	for (auto& body : engine.m_dynamic_elements)
	{
		// Properties - Dynamic
		vec2 body_pos   = to2d(body->position);
		vec2 body_speed = to2d(body->_speedPosition);

		// Bdf
		vec2 accel    = to2d(GRAVITY);
		vec2 speed    = accel * dt_sec + body_speed;
		vec2 position = accel * (dt_sec * dt_sec) / 2.0f + body_speed * dt_sec + body_pos;

		// Static objects
		for (const auto& hindrance : engine.m_static_elements)
		{
			// Properties - Static
			const vec2 hind_center		      = to2d(hindrance->position);
			std::optional<vec2> collide_point = {};
			std::optional<vec2> collide_direction = {};

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
					const vec2 line_dir = to2d(hindrance->dimensions[0]);
					const vec2 pt_a = hind_center - line_dir;
					const vec2 pt_b = hind_center + line_dir;

					if (dot(position - pt_a, line_dir) * dot(position - pt_b, line_dir) < 0) {
						float dist_line =
							std::abs((pt_b.x - pt_a.x) * (pt_a.y - position.y) - (pt_a.x - position.x) * (pt_b.y - pt_a.y)) /
							distance(pt_a, pt_b);

						if (dist_line < body_radius) {
							collide_direction = normalize(vec2(line_dir.y, -line_dir.x));
							goto compute_collide_point;
						}
					}

					if (distance(pt_a, position) < body_radius) {
						collide_direction = normalize(position - pt_a);
						goto compute_collide_point;
					}

					if (distance(pt_b, position) < body_radius) {
						collide_direction = normalize(position - pt_b);
						goto compute_collide_point;
					}

				compute_collide_point:
					if(collide_direction.has_value())
						collide_point = position - body_radius * collide_direction.value();

				} break;

				// -- Contact Sphere / Sphere
				case BaseBody::ContactType::Sphere:
				{
					float hind_radius = hindrance->dimensions[0][0];

					// Collide
					float d = distance(position, hind_center);
					if (d > hind_radius + body_radius)
						break; // No boum

					collide_direction = normalize(position - hind_center);
					collide_point = position - body_radius * collide_direction.value();
				} break;
				}

				// no boum
				if (!collide_point.has_value())
					continue;

				// boum
				vec2 u0 = collide_direction.value();
				vec2 z0 = normalize(speed);

				const float cos_a = dot(u0, z0);
				const float sin_a = sin(acos(cos_a));
				mat2 m01 = {
					+cos_a, -sin_a,
					+sin_a, +cos_a
				};
				mat2 m10 = glm::inverse(m01);

				vec2 z1 = m01 * z0;
				vec2 s1 = vec2(z1.x, -z1.y);
				vec2 s0 = m10 * s1;

				speed = body->_bouncyness * length(speed) * s0;
				position = body_pos;
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