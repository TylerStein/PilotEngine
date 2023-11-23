#include "engine_systems.h"

namespace Pilot {
	EngineSystems::EngineSystems() {
		physics = std::make_shared<SPhysics>();
		glRenderer = std::make_shared<SGLRenderer>();
	}

	void EngineSystems::Init() {
		ECS::ECS& ecs = ECS::ECS::Instance();

		ecs.RegisterComponent<Transform>();
		ecs.RegisterComponent<RigidBody>();

		ecs.RegisterComponent<Mesh>();
		ecs.RegisterComponent<Material>();

		glRenderer = ecs.RegisterSystem<SGLRenderer>();
		ECS::Signature glRendererSystemSignature;
		glRendererSystemSignature.set(ecs.GetComponentType<Transform>());
		glRendererSystemSignature.set(ecs.GetComponentType<Mesh>());
		glRendererSystemSignature.set(ecs.GetComponentType<Material>());
		ecs.SetSystemSignature<SGLRenderer>(glRendererSystemSignature);

		physics = ecs.RegisterSystem<SPhysics>();
		ECS::Signature physicsSystemSignature;
		physicsSystemSignature.set(ecs.GetComponentType<Transform>());
		physicsSystemSignature.set(ecs.GetComponentType<RigidBody>());
		ecs.SetSystemSignature<SPhysics>(physicsSystemSignature);
	}

	void EngineSystems::PhysicsUpdate() {
		physics->Update();
	}

	void EngineSystems::Update() {
	}

	void EngineSystems::RenderUpdate() {
		glRenderer->Update();
	}
}