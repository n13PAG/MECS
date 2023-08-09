#pragma once

#include "../Core/MECS.h"

namespace MECS {
	struct Velocity {
		float x;
		float y;

		Velocity() {
			x = 0;
			y = 0;
		}

		Velocity(const float& x, const float& y) {
			this->x = x;
			this->y = y;
		}

		void SetVelocity(const Vector2& velocity) {
			this->x = velocity.x;
			this->y = velocity.y;
		}
	};
}
