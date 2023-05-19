#pragma once

#include "..\Core\component.h"

namespace MECS {
	struct Position : Component {
		float x;
		float y;

		Position();
		Position(const float& x, const float& y);
		void SetPosition(const Vector2& position);
	};
}