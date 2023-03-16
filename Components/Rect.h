#pragma once

#include "..\Core\Component.h"

namespace MECS {
	struct Rect: Component {
		float width;
		float height;

		Rect();
		Rect(const float& width, const float& height);
		void SetSize(const Vector2& size);
	};
}
