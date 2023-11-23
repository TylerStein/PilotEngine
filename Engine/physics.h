#pragma once

#include "ECS.h"
#include "game_types.h"

namespace Pilot {
	class SPhysics : public ECS::System {
	public:
		float maxVelocity = 10000.0f;
		float maxForce = 10000.0f;

		void Update();
	};
}