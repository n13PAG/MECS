#pragma once

#include <stdint.h>
#include <bitset>
#include <raylib.h>

namespace MECS {

	// Entity Constants
	using Entity = std::uint32_t;
	static const Entity kMaxEntities = 400;

	// Component IDs
	// All new components must be included here
	const enum ComponentTypes {
		kPosition = 0,
		kRotation = 1,
		kRect = 2,
		kCirc = 3,
		kOutline = 4,
		kRenderable = 5,
		kText = 6,
		kCustomText = 7,
		kVelocity = 8,
		kSprite = 9,
		kAudio = 10,
		kCircleCollider = 11,
		kCompTypeNum = 12
	};

	static const uint8_t kComponentTypeCount = kCompTypeNum;

	using Signature = std::bitset<kComponentTypeCount>;
}