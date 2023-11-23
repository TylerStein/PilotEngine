#pragma once

#include <SDL.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <vector>

namespace Pilot {
	struct PColor {
		Uint8 r;
		Uint8 g;
		Uint8 b;
	};

	struct Transform {
		glm::vec2 position;
		GLint zIndex;
	};

	struct RigidBody {
		glm::vec2 size;
		glm::vec2 velocity;
		glm::vec2 acceleration;
		glm::vec2 force;
		float mass;
		float drag;
	};

	struct RawMesh {
		std::vector<GLfloat> vertexData;
		std::vector<GLuint> indexData;
	};

	struct GLMesh {
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
	};

	struct Mesh {
		RawMesh data;
		GLMesh gl;
	};

	struct Material {
		GLuint shaderProgramId;
		glm::vec4 color;
	};
}