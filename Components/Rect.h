#pragma once

#include "../Core/MECS.h"

namespace MECS {
	struct Rect {
		float width;
		float height;
		Color color;

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