#pragma once
#define SDL_MAIN_HANDLED

#include "engine_systems.h"
#include "engine_graphics.h"
#include "game.h"
#include "input.h"
#include "ecs.h"

#include <SDL.h>
#include <stdio.h>
#include <memory>
#include <gl/glew.h>
#include <gl/GLU.h>
#include <SDL_opengl.h>
#include <vector>

namespace Pilot {
	class EngineCore {
	public:
		static EngineCore& Instance() {
			if (!mInstance) {
				mInstance.reset(CreateInstance());
			}

			return *mInstance;
		}

		~EngineCore();
		int Init(const char* title,
			int x, int y, int w,
			int h);
		int Quit();
		int UpdateWindowSurface();
		int RunGame(PGame* game);

		SDL_Window* window;

		int screenWidth;
		int screenHeight;

		double deltaTime = 0;
		double clampedDeltaTime = 0;

		Input* input;
		std::shared_ptr<EngineSystems> systems;
		std::shared_ptr<EngineGraphics> graphics;

		std::vector<GLfloat> points = {
			0.0f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f
		};
	private:

		static std::unique_ptr<EngineCore> mInstance;
		static EngineCore* CreateInstance() {
			return new EngineCore();
		}

		EngineCore();
	};
}
