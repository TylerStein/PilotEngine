#include "gl_renderer.h"
#include "game_types.h"
#include "engine_core.h"

#include <glm/gtc/type_ptr.hpp>

namespace Pilot {
	void SGLRenderer::Update() {
		for (auto const& entity : mEntities) {
			Transform& transform = ECS::ECS::Instance().GetComponent<Transform>(entity);
			Mesh& mesh = ECS::ECS::Instance().GetComponent<Mesh>(entity);
			Material& material = ECS::ECS::Instance().GetComponent<Material>(entity);

			glBindVertexArray(mesh.gl.vao);

			glUseProgram(material.shaderProgramId);

			GLint posLocation = glGetUniformLocation(material.shaderProgramId, "uOffset");
			if (posLocation != -1) {
				glm::vec3 pos3 = glm::vec3(transform.position.x, transform.position.y, transform.zIndex);
				glUniform3fv(posLocation, 1, glm::value_ptr(pos3));
			}

			GLint colorLocation = glGetUniformLocation(material.shaderProgramId, "uColor");
			if (colorLocation != -1) {
				glUniform4fv(colorLocation, 1, glm::value_ptr(material.color));
			}

			glDrawElements(GL_TRIANGLES, (GLsizei)mesh.data.indexData.size(), GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}
	}
}