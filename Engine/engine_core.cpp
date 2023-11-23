#include "engine_core.h"

namespace Pilot {
	std::unique_ptr<EngineCore> EngineCore::mInstance = nullptr;

	EngineCore::EngineCore() {
		systems = nullptr;
		graphics = nullptr;
		window = nullptr;
		// screenSurface = nullptr;
		input = nullptr;
		screenHeight = 0;
		screenWidth = 0;
	}

	EngineCore::~EngineCore() {
		Quit();
	}

	int EngineCore::Init(const char* title,
		int x, int y, int w,
		int h) {

		screenWidth = w;
		screenHeight = h;
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			printf("SDL failed to init video %s\n", SDL_GetError());
			Quit();
			return 1;
		}

		window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			printf("SDL failed to create window %s\n", SDL_GetError());
			Quit();
			return 1;
		}

		graphics = std::make_unique<EngineGraphics>();
		if (graphics->Init(window) != 0) {
			printf("Graphics failed to initialize\n");
			Quit();
			return 1;
		}

		input = new Input();

		ECS::ECS& ecs = ECS::ECS::Instance();

		systems = std::make_unique<EngineSystems>();
		systems->Init();

		return 0;
	}

	int EngineCore::Quit() {
		if (window != nullptr) {
			SDL_DestroyWindow(window);
			window = nullptr;
		}

		SDL_Quit();
		return 0;
	}

	int EngineCore::UpdateWindowSurface() {
		if (window == nullptr) {
			return 1;
		}

		if (SDL_UpdateWindowSurface(window) < 0) {
			printf("SDL failed to update window surface %s\n", SDL_GetError());
			return 1;
		}

		return 0;
	}

	int EngineCore::RunGame(PGame* game) {
		game->Init();

		SDL_Event e;
		bool quit = false;

		Uint64 now = SDL_GetPerformanceCounter();
		Uint64 last = 0;

		game->Start();

		while (quit == false) {
			last = now;
			now = SDL_GetPerformanceCounter();
			deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
			clampedDeltaTime = deltaTime > 100 ? 100 : deltaTime;

			input->PreUpdate();
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = true;
					break;
				}

				input->UpdateFromEvent(&e);
			}

			game->PrePhysicsUpdate(deltaTime);
			systems->PhysicsUpdate();

			game->Update(deltaTime);
			systems->Update();

			game->PreRenderUpdate(deltaTime);

			graphics->PreDraw();
			systems->RenderUpdate();
			graphics->Draw(window);

			game->PostRenderUpdate(deltaTime);
		}
		game->End();
		return 0;
	}
}
