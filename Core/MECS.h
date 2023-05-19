#pragma once

#include <stdint.h>
#include <bitset>
#include <raylib.h>

namespace MECS {

	// Entity Constants
	using Entity = std::uint32_t;
	static const Entity MAX_ENTITIES = 800;

	// Component Constants
	//using ComponentType = uint8_t;

	// TODO Change to the number of types
	static const uint8_t MAX_COMPONENTS_PER_ENTITY = 32;
	//using Signature = std::bitset<MAX_COMPONENTS_PER_ENTITY>;

	// Component IDs
	// All new components must be included here
	//const enum ComponentTypes { 
	//	POSITION = 0, 
	//	ROTATION = 1, 
	//	RECT = 2, 
	//	CIRC = 3, 
	//	OUTLINE = 4, 
	//	RENDERABLE = 5, 
	//	TEXT = 6, 
	//	CUSTOMTEXT = 7, 
	//	VELOCITY = 8, 
	//	SPRITE = 9, 
	//	AUDIO = 10,
	//	MAX_NUM_TYPES = 11
	//};

	//static const uint8_t COMPONENT_TYPE_COUNT = MAX_NUM_TYPES;
}