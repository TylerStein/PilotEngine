#pragma once

#include "object.h"
#include "game_types.h"

namespace Pilot {
	class SceneObject : public PObject {
	public:
		SceneObject() : SceneObject("New SceneObject") {}
		SceneObject(std::string name) : PObject(name) {
			transform = &AddComponent<Transform>();
		}
	private:
		Transform* transform;
	};

}