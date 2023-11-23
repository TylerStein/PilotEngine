#pragma once

#include "game_types.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <stdio.h>
#include <string>
#include <memory>

namespace Pilot {
	class EngineGraphics {
	public:
		static const char* BasicFragment;
		static const char* BasicVertex;

		EngineGraphics();
		int Init(SDL_Window* window);
		void PreDraw();
		void Draw(SDL_Window* window);
		void SetClearColor(GLfloat r, GLfloat g, GLfloat b);

		Mesh CreateMesh(RawMesh meshData);
		void DestroyMesh(std::shared_ptr<Mesh> mesh);

		GLuint CompileShader(const std::string& shaderSource, GLenum type);
		GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	private:
		bool vsync = true;
		GLfloat mClearColor[4] = { 0.f, 0.f, 0.f, 1.f };
		GLuint mVbo = 0;
		GLuint mVao = 0;
	};
}