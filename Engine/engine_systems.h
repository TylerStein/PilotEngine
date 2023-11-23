#pragma once

#include "physics.h"
#include "gl_renderer.h"

namespace Pilot {
	class EngineSystems {
	public:
		EngineSystems();

		void Init();

		// physics
		void PhysicsUpdate();

		// game logic
		void Update();

		// rendering
		void RenderUpdate();

		std::shared_ptr<SPhysics> physics;
		std::shared_ptr<SGLRenderer> glRenderer;
	};
}