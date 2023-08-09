#pragma once

#include "MECS.h"

#include "../Core/component_manager.h"
#include "../Core/entity_manager.h"
#include "../Core/system_manager.h"

namespace MECS {
	class Coordinator {
	private:
		ComponentManager component_manager;
		EntityManager entity_manager;
		SystemManager system_manager;
	public:
		virtual void Init() {};

#pragma region Entity Management
		Entity CreateEntity() {
			if (entity_manager.CanCreateEntity()) {
				return entity_manager.CreateEntity();
			}
			else {
				return -1;
			}
		}

		void DestroyEntity(Entity entity_id) {
			Signature sig = entity_manager.GetSignature(entity_id);
			component_manager.RemoveAllComponents(entity_id, sig);
			
			// Clear entity signature
			entity_manager.RemoveSignatureBit(entity_id, sig);

			system_manager.ReassignEntity(entity_id, GetSignature(entity_id));
			entity_manager.DestroyEntity(entity_id);
		}

		Signature GetSignature(Entity entity_id) {
			return entity_manager.GetSignature(entity_id);
		}
#pragma endregion

#pragma region Component Management
		template<typename T>
		void RegisterComponentType() {
			component_manager.RegisterComponentArray<T>();
		}

		template<typename T>
		void RegisterComponentType(ComponentType component_type) {
			component_manager.RegisterComponentArray<T>(component_type);
		}

		template<typename T>
		T& AddComponent(Entity entity_id) {
			auto& component = component_manager.AddComponent<T>(entity_id);
			ComponentType comp_type = component_manager.GetComponentType<T>();
			entity_manager.AddSignatureBit(entity_id, comp_type);
			//system_manager.AddEntityToUpdate(entity_id, entity_manager.GetSignature(entity_id));
			system_manager.ReassignEntity(entity_id, entity_manager.GetSignature(entity_id));

			return component;
		}

		template<typename T>
		void RemoveComponent(Entity entity_id) {
			entity_manager.RemoveSignatureBit(entity_id, component_manager.GetComponentType<T>());
			component_manager.RemoveComponent<T>(entity_id);
			//system_manager.AddEntityToUpdate(entity_id, entity_manager.GetSignature(entity_id));
			system_manager.ReassignEntity(entity_id, entity_manager.GetSignature(entity_id));
		}

		template<typename T>
		T& GetComponent(Entity entity_id) {
			return component_manager.GetComponent<T>(entity_id);
		}
#pragma endregion

#pragma region System Management
		template<typename T>
		void AddToSystemSignature(std::shared_ptr<System> sys) {
			sys->AddToSystemSignature(component_manager.GetComponentType<T>());
		}

		void RegisterSystem(std::shared_ptr<System> system) {
			system_manager.RegisterSystem(system);
		}

		void ReassignEntityToSystems(Entity entity_id) {
			system_manager.ReassignEntity(entity_id, entity_manager.GetSignature(entity_id));
		}

		void ReassignAllChangedEntitiesToSystems() {
			system_manager.ReassignAllEntities();
		}
#pragma endregion

	};
}
