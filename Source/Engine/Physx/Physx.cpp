#include "Physx.hpp"
#include "../Events/CustomEvents.hpp"

#include <reactphysics3d/reactphysics3d.h>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>

#include <optional>
#include <vector>
#include <iostream>

using namespace glm;
using namespace reactphysics3d;

// Private impl
struct Physx::_impl
{
	struct BodyElement {
		std::shared_ptr<BaseBody> body;
		RigidBody* rigid;
	};

	Physx::_impl() :
		world(nullptr)
	{
		// Setup
		PhysicsWorld::WorldSettings settings;
		settings.gravity = Vector3(0.0f, 0.0f, -9.81f);

		// Create
		world = factory.createPhysicsWorld(settings);
	}

	// Hidden members
	PhysicsCommon factory;
	PhysicsWorld* world;
	std::unordered_set<std::shared_ptr<BodyElement>> bodies;
};

// Private
Physx& Physx::_get() {
	static Physx physx;
	return physx;
}

Physx::Physx() : p_impl(std::make_unique<_impl>()) 
{
	// ...
}
Physx::~Physx() 
{
	// Need a body
}

// Public
void Physx::Add(std::shared_ptr<BaseBody> body, BodyType type) {
	auto& px = _get().p_impl;
	auto& world = px->world;

	// Convert pose(position, orientation) to world referential
	Transform pose(Vector3(body->position.x, body->position.y, body->position.z), Quaternion::identity());

	// Create physical object
	RigidBody* phxBody = world->createRigidBody(pose);
	phxBody->setType(([=]() -> ::BodyType {
		switch (type) {
		case BodyType::Dynamic: return ::BodyType::DYNAMIC;
		case BodyType::Static:  return ::BodyType::STATIC;
		}
		return ::BodyType::KINEMATIC; // whatever that means
	})());

	// Add to world and memory
	px->bodies.insert(
		std::make_shared<_impl::BodyElement>(_impl::BodyElement { body, phxBody })
	);
}

void Physx::Clear() {
	auto& px = _get().p_impl;
	auto& world = px->world;

	// Remove from world
	for (auto elt : px->bodies) {
		world->destroyRigidBody(elt->rigid);
	}

	// Remove from memory
	px->bodies.clear();
}

void Physx::Compute(float delta_time_ms) {
	Physx& engine(_get());
	_impl& engine_impl = *engine.p_impl;

	// Magie here
	engine_impl.world->update(delta_time_ms / 1000.0f);

	// Update drawn bodies
	for (auto& element : engine_impl.bodies) {
		const Transform& transform = element->rigid->getTransform();
		const Vector3& position = transform.getPosition();
		
		element->body->position = vec3(position.x, position.y, position.z);

		// to do, add orientations..
	}
}