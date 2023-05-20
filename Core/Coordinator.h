#pragma once

#include "MECS.h"

#include "../Core/component_manager.h"
#include "../Core/entity_manager.h"

namespace MECS {
	class Coordinator {
	private:
		ComponentManager component_manager;
		EntityManager entity_manager;
	public:
		Entity CreateEntity() {
			return entity_manager.CreateEntity();
		}

		void DestroyEntity(Entity entity_id) {
			component_manager.RemoveAllComponents(entity_id, entity_manager.GetSignature(entity_id));
			entity_manager.DestroyEntity(entity_id);
		}

		template<typename T>
		void AddComponent(Entity entity_id) {
			entity_manager.AddSignatureBit<T>(entity_id, component_manager.AddComponent<T>(entity_id));
		}

		template<typename T>
		void RemoveComponent(Entity entity_id) {
			entity_manager.RemoveSignatureBit<T>(entity_id, component_manager.GetComponentType<T>());
			component_manager.RemoveComponent<T>(entity_id);
		}

		template<typename T>
		T& GetComponent(Entity entity_id) {
			return component_manager.GetComponent<T>(entity_id);
		}
	};
}
