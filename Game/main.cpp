#include "main.h"
#include "game.h"

#include <engine_core.h>
#include <stdio.h>

int main(int argc, char* args[]) {
	Pilot::EngineCore::Instance().Init("SDLTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);
	Game* game = new Game();
	Pilot::EngineCore::Instance().RunGame(game);
	Pilot::EngineCore::Instance().Quit();
	delete game;
	return 0;
}