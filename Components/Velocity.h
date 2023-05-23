#pragma once

#include "..\Core\component.h"

namespace MECS {
	struct Velocity : Component {
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
