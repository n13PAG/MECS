#pragma once

#include "..\Core\Component.h"

namespace MECS {
	struct Velocity : Component {
		float x;
		float y;

		Velocity();
		Velocity(const float& x, const float& y);
		void SetVelocity(const Vector2& velocity);
	};
}
