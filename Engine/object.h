#pragma once

#include "ecs.h"

namespace Pilot {
	class PObject {
	public:
		PObject() : PObject("New PObject") {}

		PObject(std::string name) {
			mName = name;
			mEntity = ECS::ECS::Instance().CreateEntity();
		}

		~PObject() {
			ECS::ECS::Instance().DestroyEntity(mEntity);
		}

		template<typename T>
		T& AddComponent() {
			ECS::ECS::Instance().AddComponent(mEntity, T{});
			return GetComponent<T>();
		}

		template<typename T>
		T& AddComponent(T component) {
			ECS::ECS::Instance().AddComponent(mEntity, component);
			return GetComponent<T>();
		}

		template<typename T>
		T& GetComponent() {
			return ECS::ECS::Instance().GetComponent<T>(mEntity);
		}
	private:
		ECS::Entity mEntity;
		std::string mName;
	};
}