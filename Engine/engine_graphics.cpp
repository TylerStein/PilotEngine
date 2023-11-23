#include "engine_graphics.h"
#include "shaders.h"

namespace Pilot {
	const char* EngineGraphics::BasicVertex = R"(#version 450 core
layout (location = 0) in vec3 aPos; // The position variable has attribute position 0
uniform vec3 uOffset; // Uniform offset variable

void main() {
    gl_Position = vec4(aPos.x + uOffset.x, aPos.y + uOffset.y, aPos.z + uOffset.z, 1.0); // Directly output the position
})";

	const char* EngineGraphics::BasicFragment = R"(#version 450 core
out vec4 FragColor;
uniform vec4 uColor; // Uniform color variable

void main() {
    FragColor = uColor; // Set the uniform color
})";

	EngineGraphics::EngineGraphics() {

	}

	int EngineGraphics::Init(SDL_Window* window) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		SDL_GLContext ctx = SDL_GL_CreateContext(window);
		if (ctx == NULL) {
			printf("Failed to get SDL context %s\n", SDL_GetError());
			return 1;
		}

		glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK) {
			printf("GLEW failed to initialize %s\n", glewGetErrorString(glewError));
			return 1;
		}

		if (vsync) {
			SDL_GL_SetSwapInterval(1);
		}

		return 0;
	}

	void EngineGraphics::SetClearColor(GLfloat r, GLfloat g, GLfloat b) {
		mClearColor[0] = r;
		mClearColor[1] = g;
		mClearColor[2] = b;
	}

	void EngineGraphics::PreDraw() {
		glClearColor(mClearColor[0], mClearColor[1], mClearColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void EngineGraphics::Draw(SDL_Window* window) {
		SDL_GL_SwapWindow(window);
	}

	Mesh EngineGraphics::CreateMesh(RawMesh meshData) {
		GLMesh glMesh{0, 0, 0};
		glGenVertexArrays(1, &glMesh.vao);
		glGenBuffers (1, &glMesh.vbo);
		glGenBuffers(1, &glMesh.ebo);

		glBindVertexArray(glMesh.vao);
		
		glBindBuffer(GL_ARRAY_BUFFER, glMesh.vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * meshData.vertexData.size(), &meshData.vertexData.front(), GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glMesh.ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * meshData.indexData.size(), &meshData.indexData.front(), GL_STATIC_DRAW);

		// assumes only 3 values per vertex, increase size to include more data (eg. normals, texture coords)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return Mesh{ meshData, glMesh };
	}

	void EngineGraphics::DestroyMesh(std::shared_ptr<Mesh> mesh) {
		// TODO
	}


	GLuint EngineGraphics::CompileShader(const std::string& shaderSource, GLenum type) {
		GLuint shader = glCreateShader(type);
		const char* source = shaderSource.c_str();
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);

		GLint success;
		GLchar infoLog[1024];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			printf("Shader compilation error (type %d) %s\n", (int)type, infoLog);
			return NULL;
		}

		return shader;
	}

	GLuint EngineGraphics::CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
		GLuint vertexShader = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
		GLuint fragmentShader = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		GLint success;
		GLchar infoLog[1024];

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
			printf("Shader linking error %s\n", infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgram;
	}
}