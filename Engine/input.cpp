#include "Input.h"

namespace Pilot {
	void Input::PreUpdate() {
		fire.pressed = false;
		fire.released = false;
		jump.pressed = false;
		jump.released = false;
		mousemoved = false;
	}

	void Input::UpdateFromEvent(SDL_Event* e) {
		const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
		if (keyStates == nullptr) {
			return;
		}
		
		if (e->type == SDL_MOUSEMOTION) {
			SDL_GetMouseState(&mousex, &mousey);
			mousemoved = true;
		}

		if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
			switch (e->key.keysym.sym) {
			case SDLK_w: move.y = 1; break;
			case SDLK_d: move.x = 1; break;
			case SDLK_s: move.y = -1; break;
			case SDLK_a: move.x = -1; break;
			case SDLK_f: fire.pressed = true; fire.held = true; break;
			case SDLK_SPACE: jump.pressed = true; jump.held = true; break;
			}
		}

		if (e->type == SDL_KEYUP && e->key.repeat == 0) {
			switch (e->key.keysym.sym) {
			case SDLK_w: move.y = 0; break;
			case SDLK_d: move.x = 0; break;
			case SDLK_s: move.y = 0; break;
			case SDLK_a: move.x = 0; break;
			case SDLK_f: fire.released = true; fire.held = false; break;
			case SDLK_SPACE: jump.released = true; jump.held = false; break;
			}
		}
	}
}
