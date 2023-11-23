#include "physics.h"
#include "game_types.h"
#include "engine_core.h"

namespace Pilot {
	void SPhysics::Update() {
		// use clamped deltaTime so physics don't freak out if the execution pauses
		float deltaTime = (float)EngineCore::Instance().clampedDeltaTime;
		glm::vec2 bounds = glm::vec2(EngineCore::Instance().screenWidth, EngineCore::Instance().screenHeight);

		for (auto const& entity : mEntities) {
			RigidBody& rigidbody = ECS::ECS::Instance().GetComponent<RigidBody>(entity);
			Transform& transform = ECS::ECS::Instance().GetComponent<Transform>(entity);
			glm::vec2 dtVec = glm::vec2(deltaTime, deltaTime);

			// forces
			rigidbody.force = rigidbody.force + (rigidbody.velocity * -rigidbody.drag);
			float forceLen = glm::length(rigidbody.force);
			if (forceLen > maxForce) {
				rigidbody.force = glm::normalize(rigidbody.force) * maxForce;
			}

			rigidbody.acceleration = rigidbody.force / rigidbody.mass;

			rigidbody.velocity = rigidbody.velocity + (rigidbody.acceleration * dtVec);
			float velocityLen = glm::length(rigidbody.velocity);
			if (velocityLen > maxVelocity) {
				rigidbody.velocity = glm::normalize(rigidbody.velocity) * maxVelocity;
			}

			transform.position = transform.position + (rigidbody.velocity * dtVec);

			// bound x
			if (transform.position.x + rigidbody.size.x > bounds.x) {
				transform.position.x = bounds.x - rigidbody.size.x - 1;
				rigidbody.velocity.x = -rigidbody.velocity.x;
			}
			else if (transform.position.x < 0) {
				transform.position.x = 1;
				rigidbody.velocity.x = -rigidbody.velocity.x;
			}

			// bound y
			if (transform.position.y + rigidbody.size.y > bounds.y) {
				transform.position.y = bounds.y - rigidbody.size.y - 1;
				rigidbody.velocity.y = -rigidbody.velocity.y;
			}
			else if (transform.position.y < 0) {
				transform.position.y = 1;
				rigidbody.velocity.y = -rigidbody.velocity.y;
			}
			
			// reset force
			rigidbody.force.x = 0;
			rigidbody.force.y = 0;
		}
	}
}