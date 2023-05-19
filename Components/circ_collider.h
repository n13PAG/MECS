#pragma once

#include "../Core/component.h"

namespace MECS {
	struct CircleCollider : Component {
		Vector2 position;
		float radius;

		CircleCollider();
		CircleCollider(const Vector2& pos, const float& radius);
		void SetPosition(const Vector2& pos);
	};
}
