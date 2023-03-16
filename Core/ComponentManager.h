#pragma once

#include <assert.h>
#include <unordered_map>

#include "Component.h"

namespace MECS {
	//struct ComponentManager {
	//private:
	//	size_t mAvailableComponents = MAX_ENTITIES;
	//	size_t mActiveComponentCount = 0;

	//	// Component Packed array 
	//	Component components[MAX_ENTITIES];
	//	
	//	// Map of entities to the associated component index in the packed array
	//	std::unordered_map<Entity, size_t> mEntityToComponentIndex;

	//public:
	//	size_t GetActiveComponentCount() {
	//		return mActiveComponentCount;
	//	}

	//	void RegisterComponent(Entity entity, Component)
	//};
}