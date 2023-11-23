#pragma once

#include <engine_core.h>
#include <game.h>
#include <ecs.h>
#include <game_types.h>
#include <scene_object.h>
#include <glm/glm.hpp>

class Game : public Pilot::PGame
{
public:
	Game();

	virtual void Init() override;
	virtual void Start() override;
	virtual void PrePhysicsUpdate(double deltaTime) override;
	virtual void Update(double deltaTime) override;
	virtual void PreRenderUpdate(double deltaTime) override;
	virtual void PostRenderUpdate(double deltaTime) override;
	virtual void End() override;
private:
	Pilot::SceneObject* mPlayer;

	int mPlayerColorIndex = 0;
	int mMaxPlayerColorIndex = 2;
	glm::vec4 mPlayerColors[3] = {
		glm::vec4{0.f, 1.f, 1.f, 1.f},
		glm::vec4{1.f, 0.f, 1.f, 1.f},
		glm::vec4{1.f, 1.f, 0.f, 1.f},
	};

	float mTimescale = 0.0001f;
	float mPlayerSpeed = 30.0f;
	float mPlayerMass = 10.0f;
	float mPlayerDrag = 0.4f;
	float mGravity = 20.0f;
};

