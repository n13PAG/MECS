#pragma once

#include "../Core/component.h"

namespace MECS {
	struct Rect : Component {
		float width;
		float height;

		Rect() {
			width = 0;
			height = 0;
		}

		Rect(const float& width, const float& height) {
			this->width = width;
			this->height = height;
		}

		void SetSize(const Vector2& size) {
			this->width = size.x;
			this->height = size.y;
		}
	};
}