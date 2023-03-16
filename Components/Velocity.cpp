#include "Velocity.h"

using namespace MECS;

Velocity::Velocity() {
	Type.reset();
	Type.flip(VELOCITY);
}

Velocity::Velocity(const float& x, const float& y) {
	Velocity();
	this->x = x;
	this->y = y;
}

void Velocity::SetVelocity(const Vector2& velocity) {
	x = velocity.x;
	x = velocity.y;
}
