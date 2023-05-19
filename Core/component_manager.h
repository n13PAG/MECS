#pragma once

#include "component.h"

#include "../Components/position.h"
#include "../Components/rotation.h"
#include "../Components/rect.h"
#include "../Components/circ.h"
#include "../Components/outline.h"
#include "../Components/renderable.h"
#include "../Components/velocity.h"
#include "../Components/circ_collider.h"

#include <assert.h>
#include <array>
#include <memory>
#include <unordered_map>

namespace MECS {

	class IComponentArray {
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity_id) = 0;
	};

	template<typename T>
	class ComponentArray : public IComponentArray{
	private:
		size_t available_components_ = MAX_ENTITIES;
		size_t active_component_count = 0;

		// Component Packed array
		std::array<T, MAX_ENTITIES> components_;

		std::unordered_map<Entity, size_t> entity_to_component_index_;
		std::unordered_map<size_t, Entity> component_index_to_entity_;

	public:

		size_t GetComponentNum() {
			return active_component_count;
		}

		void AddComponent(Entity entity_id) {
			// Triggers if : No more components can be registered
			assert(available_components_ > 0);

			// Get index of first available component
			size_t index = MAX_ENTITIES - available_components_;

			// Triggers if : Index is out of range
			assert(index < MAX_ENTITIES&& index >= 0);

			// Set entity to component index association
			entity_to_component_index_[entity_id] = index;

			// Set component index to entity assocation
			component_index_to_entity_[index] = entity_id;

			active_component_count++;
			available_components_--;

			/*return &components_[index];*/
		}

		void RemoveComponent(Entity entity_id) {
			// Trigger if : Getting a non-existent component
			assert(entity_to_component_index_.find(entity_id) != entity_to_component_index_.end());

			size_t target_comp_index = entity_to_component_index_[entity_id];
			size_t last_component_index = active_component_count - 1;

			// Check if the component to be removed is the last component
			if (target_comp_index == last_component_index) {
				entity_to_component_index_.erase(entity_id);
			}
			else {
				// Cache id associate with last component
				Entity moved_entity = component_index_to_entity_[last_component_index];

				// Swap target component with last component
				std::swap(components_[target_comp_index], components_[last_component_index]);

				// Remove entity associated with array index
				entity_to_component_index_.erase(entity_id);

				// Remove moved entity's associated outdated array index
				entity_to_component_index_.erase(moved_entity);

				// Create to assocation
				entity_to_component_index_[moved_entity] = target_comp_index;
			}

			active_component_count--;
			available_components_++;
		}

		void EntityDestroyed(Entity entity_id) override {
			if (entity_to_component_index_.find(entity_id) != entity_to_component_index_.end()) {
				RemoveComponent(entity_id);
			}
		}

		T& GetComponent(Entity entity_id) {
			// Trigger if : Getting a non-existent component
			assert(entity_to_component_index_.find(entity_id) != entity_to_component_index_.end());

			return components_[entity_to_component_index_[entity_id]];
		}
	};

	class ComponentManager {
	private:
		std::vector<std::shared_ptr<IComponentArray>> componentArrays_;
		std::array<const char*, kComponentTypeCount> componentTypes_;
		size_t registered_types_ = 0;


	public:

		ComponentManager() {
			std::cout << "Component Manager";
			RegisterComponentArray<Position>();
			RegisterComponentArray<Rotation>();
		}

		template<typename T>
		void RegisterComponentArray() {

			const char* type_name = typeid(T).name();

			//for (auto type : componentTypes_) {
			//	// Triggers if : Component type is already registered
			//	//assert(type != type_name);
			//}

			componentTypes_[registered_types_] = type_name;
			componentArrays_.push_back(std::make_shared<ComponentArray<T>>());
			registered_types_++;
		}

		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray() {
			const char* type_name = typeid(T).name();
			size_t index = 0;
			for (auto type : componentTypes_) {
				if (type == type_name) {
					return std::static_pointer_cast<ComponentArray<T>>(componentArrays_[index]);
				}
				index++;
			}

			// Triggers if : Component array of this type was not registered
			assert(index == 0);
		}

		template<typename T>
		void AddComponent(Entity entity_id) {
			GetComponentArray<T>()->AddComponent(entity_id);
		}

		template<typename T>
		void RemoveComponent(Entity entity_id) {
			GetComponentArray<T>()->RemoveComponent(entity_id);
		}

		template<typename T>
		T& GetComponent(Entity entity_id) {
			return GetComponentArray<T>()->GetComponent(entity_id);
		}
	};
}