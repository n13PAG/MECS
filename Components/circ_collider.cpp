#include "circ_collider.h"

namespace MECS {
	CircleCollider::CircleCollider() {
		type = kCircleCollider;
		position = { 0, 0 };
		radius = 0;
	}

	CircleCollider::CircleCollider(const Vector2& pos, const float& radius) {
		CircleCollider();
		position = pos;
		this->radius = radius;
	}

	void CircleCollider::SetPosition(const Vector2& pos) {
		position = pos;
	}
}


