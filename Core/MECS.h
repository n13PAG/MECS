#pragma once

#include <stdint.h>
#include <bitset>
#include <raylib.h>

namespace MECS {

	// Entity Constants
	using Entity = std::uint32_t;
	static const Entity MAX_ENTITIES = 800;

	// Component Constants
	using ComponentType = uint8_t;
	static const uint8_t MAX_COMPONENTS_PER_ENTITY = 32;
	using Signature = std::bitset<MAX_COMPONENTS_PER_ENTITY>;

	// Component IDs
	// All new components must be included here
	const enum ComponentIDs { POSITION, 
		ROTATION, 
		RECT, 
		CIRC, 
		OUTLINE, 
		RENDERABLE, 
		TEXT, 
		CUSTOMTEXT, 
		VELOCITY, 
		SPRITE, 
		AUDIO };
}