#pragma once

#include <stdint.h>
#include <bitset>
#include <raylib.h>

namespace MECS {

	// Entity Constants
	using Entity = std::uint32_t;
	static const Entity kMaxEntities = 200;

	// Component IDs
	// All new components must be included here
	const enum ComponentTypes {
		kTransform,
		kRect,
		kCirc,
		kOutline,
		kRenderable,
		kText,
		kCustomText,
		kVelocity,
		kSprite,
		kAudio,
		kCircleCollider,
		kAdvParticle2D_Rect,
		kUI_Button,
		kCompTypeNum
	};

	static const uint8_t kComponentTypeCount = kCompTypeNum;

	using Signature = std::bitset<kComponentTypeCount>;
	using ComponentType = Signature;

}