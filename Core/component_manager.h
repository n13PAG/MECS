#pragma once

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
		size_t available_components_ = kMaxEntities;
		size_t active_component_count = 0;

		// Component Packed array
		std::array<T, kMaxEntities> components_;

		std::unordered_map<Entity, size_t> entity_to_component_index_;
		std::unordered_map<size_t, Entity> component_index_to_entity_;

	public:

		size_t GetComponentNum() {
			return active_component_count;
		}

		T& AddComponent(Entity entity_id) {
			// Triggers if : No more components can be registered
			assert(available_components_ > 0);

			// Get index of first available component
			size_t index = kMaxEntities - available_components_;

			// Triggers if : Index is out of range
			assert(index < kMaxEntities&& index >= 0);

			// Set entity to component index association
			entity_to_component_index_[entity_id] = index;

			// Set component index to entity assocation
			component_index_to_entity_[index] = entity_id;

			active_component_count++;
			available_components_--;

			return components_[entity_to_component_index_[entity_id]];
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
	protected:
		std::vector<std::shared_ptr<IComponentArray>> componentArrays_;
		std::vector<const char*> component_type_names_;
		std::unordered_map<const char*, ComponentType> component_signatures_map_;
		size_t registered_types_ = 0;


	public:

		ComponentManager() {
		}

		template<typename T>
		void RegisterComponentArray() {

			const char* type_name = typeid(T).name();

			for (auto type : component_type_names_) {
				//Triggers if : Component type is already registered
				assert(type != type_name && "Component type is already registered");
			}

			// Add name of component to list
			component_type_names_.push_back(type_name);

			// Add component array 
			componentArrays_.push_back(std::make_shared<ComponentArray<T>>());

			// Use index to construct signature
			Signature sig = 0;
			sig.reset();
			sig.flip(registered_types_);

			// Insert signature to map
			component_signatures_map_.insert({ type_name, sig });

			registered_types_++;
		}

		template<typename T>
		void RegisterComponentArray(ComponentType component_type) {
			const char* type_name = typeid(T).name();

			for (auto type : component_type_names_) {
				for (auto type : component_type_names_) {
					//Triggers if : Component type is already registered
					assert(type != type_name && "Component type is already registered");
				}
			}

			// Add name of component to list
			component_type_names_.push_back(type_name);

			// Add component array 
			componentArrays_.push_back(std::make_shared<ComponentArray<T>>());

			// Insert signature to map
			component_signatures_map_.insert({ type_name, component_type });

			registered_types_++;
		}

		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray() {
			const char* type_name = typeid(T).name();
			size_t index = 0;
			for (auto type : component_type_names_) {
				if (type == type_name) {
					return std::static_pointer_cast<ComponentArray<T>>(componentArrays_[index]);
				}
				index++;
			}

			// Triggers if : Component array of this type was not registered
			assert(index == 0);
		}

		//template<typename T>
		//ComponentType AddComponent(Entity entity_id) {
		//	GetComponentArray<T>()->AddComponent(entity_id);
		//	return component_signatures_map_[typeid(T).name()];
		//}

		template<typename T>
		T& AddComponent(Entity entity_id) {
			return GetComponentArray<T>()->AddComponent(entity_id);
		}

		template<typename T>
		void RemoveComponent(Entity entity_id) {
			GetComponentArray<T>()->RemoveComponent(entity_id);
		}

		template<typename T>
		T& GetComponent(Entity entity_id) {
			return GetComponentArray<T>()->GetComponent(entity_id);
		}

		template<typename T>
		ComponentType GetComponentType() {
			return component_signatures_map_[typeid(T).name()];
		}

		ComponentType GetComponentType(const char* name) {
			return component_signatures_map_[name];
		}

		void RemoveAllComponents(Entity entity_id, Signature signature) {
			for (size_t i = 0; i < component_type_names_.size(); i++) {
				ComponentType component_type = component_signatures_map_[component_type_names_[i]];

				if ((signature & component_type) == component_type) {
					componentArrays_[i]->EntityDestroyed(entity_id);
				}
			}
		}
	};
}