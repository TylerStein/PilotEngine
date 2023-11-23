#pragma once
#include "ecs.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <stdio.h>
#include <string>

namespace Pilot {
	class SGLRenderer : public ECS::System {
	public:
		void Update();

	private:
		GLint mVertexPos2DLocation = -1;
		GLuint mVbo = 0;
		GLuint mVao = 0;
	};
}