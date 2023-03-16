#pragma once

#include <stdint.h>

namespace NECS {

	const enum ComponentIDs {TRANSFORM, ROTATION, RECT, CIRC, OUTLINE, RENDERABLE, TEXT, CUSTOMTEXT, VELOCITY, SPRITE, AUDIO};
	using ComponentType = uint8_t;

	struct Component {
		ComponentType ID;
	};
}

