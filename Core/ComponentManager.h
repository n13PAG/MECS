#pragma once

#include <assert.h>
#include <unordered_map>

#include "Component.h"

namespace MECS {
	template<typename T>
	struct ComponentManager {
	private:
		size_t mAvailableComponents = MAX_ENTITIES;
		size_t mActiveComponentCount = 0;

		// Component Packed array 
		T mComponents[MAX_ENTITIES];
		
		// Map of entities to the associated component index in the packed array
		std::unordered_map<Entity, size_t> mEntityToComponentIndex;

		// Map of component indices to their associated entity IDs
		std::unordered_map<size_t, Entity> mComponentIndexToEntity;

	public:
		size_t GetActiveComponentCount() {
			return mActiveComponentCount;
		}

		T* RegisterComponent(Entity entity) {
			// Trigger if : No more components can be registered
			assert(mAvailableComponents > 0);

			// Get index of first available component
			size_t index = MAX_ENTITIES - mAvailableComponents;

			// Triggers if : Index is out of range
			assert(index < MAX_ENTITIES&& index >= 0);

			// Set entity to index association
			mEntityToComponentIndex[entity] = index;

			// Set index to associated entity
			mComponentIndexToEntity[index] = entity;

			mActiveComponentCount++;
			mAvailableComponents--;

			return &mComponents[index];
		}

		void RemoveComponent(Entity entity) {
			// Trigger if : Getting a non-existent component
			assert(mEntityToComponentIndex.find(entity) != mEntityToComponentIndex.end());

			size_t index_RemovedComponent = mEntityToComponentIndex[entity];
			size_t index_LastComponent = mActiveComponentCount - 1;

			// The component to be removed is the last element
			if (index_LastComponent == index_RemovedComponent) {

				mEntityToComponentIndex.erase(entity);

				mActiveComponentCount--;
				mAvailableComponents++;

				return;
			}

			// Cache id of the moved entity
			Entity movedEntity = mComponentIndexToEntity[index_LastComponent];

			// Swap the last array element to the newly available index
			std::swap(mComponents[index_LastComponent], mComponents[index_RemovedComponent]);

			// Remove entity associated with array index
			mEntityToComponentIndex.erase(entity);

			// Remove moved entity's associated outdated array index
			mEntityToComponentIndex.erase(movedEntity);

			// Add new association
			mEntityToComponentIndex[movedEntity] = index_RemovedComponent;

			mActiveComponentCount--;
			mAvailableComponents++;
		}

		T* GetComponent(Entity entity) {
			// Triggers if : Getting a non-existent component
			assert(mEntityToComponentIndex.find(entity) != mEntityToComponentIndex.end());

			return &mComponents[mEntityToComponentIndex[entity]];
		}
	};
}