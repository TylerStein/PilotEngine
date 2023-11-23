#include "game.h"

#include <glm/glm.hpp>
#include <primitives.h>
#include <shaders.h>

using namespace Pilot;

Game::Game() {
	mPlayer = nullptr;
}

void Game::Init() {
	EngineCore& engine = EngineCore::Instance();
	ECS::ECS& ecs = ECS::ECS::Instance();

	engine.graphics->SetClearColor(0.16f, 0.16f, 0.16f);

	mPlayer = new SceneObject("Player");

	Mesh mesh = engine.graphics->CreateMesh(PrimitiveQuad());
	auto shaderProgramId = engine.graphics->CreateShaderProgram(EngineGraphics::BasicVertex, EngineGraphics::BasicFragment);
	Material material = Material{ shaderProgramId, mPlayerColors[mPlayerColorIndex] };

	mPlayer->AddComponent(mesh);
	mPlayer->AddComponent(material);
}

void Game::Start() {
}

void Game::PrePhysicsUpdate(double deltaTime) {

}

void Game::Update(double deltaTime) {
	EngineCore& engine = EngineCore::Instance();
	ECS::ECS& ecs = ECS::ECS::Instance();

	float dt = (float)deltaTime * mTimescale;

	if (engine.input->jump.pressed) {
		mPlayerColorIndex++;
		if (mPlayerColorIndex > mMaxPlayerColorIndex) {
			mPlayerColorIndex = 0;
		}

		Material& playerMaterial = mPlayer->GetComponent<Material>();
		playerMaterial.color = mPlayerColors[mPlayerColorIndex];
	}

	Transform& transform = mPlayer->GetComponent<Transform>();
	transform.position.x += engine.input->move.x * mPlayerSpeed * dt;
	transform.position.y += engine.input->move.y * mPlayerSpeed * dt;
}

void Game::PreRenderUpdate(double deltaTime) {

}


void Game::PostRenderUpdate(double deltaTime) {

}

void Game::End() {
	delete mPlayer;
	mPlayer = nullptr;
}
