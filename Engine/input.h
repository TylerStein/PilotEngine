#pragma once
#include <SDL.h>

namespace Pilot {
	struct BinaryInputAction {
	public:
		bool released = false;
		bool pressed = false;
		bool held = false;
	};

	struct Axis2DInputAction {
	public:
		float x = 0;
		float y = 0;
	};

	class Input {
	public:
		void PreUpdate();
		void UpdateFromEvent(SDL_Event* e);
		BinaryInputAction fire;
		BinaryInputAction jump;
		Axis2DInputAction look;
		Axis2DInputAction move;
		int mousex = 0, mousey = 0;
		bool mousemoved;
	};

}