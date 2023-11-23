#pragma once

namespace Pilot {
	class PGame {
	public:
		// pre-setup
		virtual void Init() = 0;

		// pre-loop
		virtual void Start() = 0;

		// pre-physics
		virtual void PrePhysicsUpdate(double deltaTime) = 0;

		// general gameplay, pre-ecs-process
		virtual void Update(double deltaTime) = 0;
		
		// pre-render
		virtual void PreRenderUpdate(double deltaTime) = 0;

		// post-render
		virtual void PostRenderUpdate(double deltaTime) = 0;

		// post-loop
		virtual void End() = 0;
	};
}
