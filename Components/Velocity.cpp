#include "Velocity.h"

using namespace MECS;

Velocity::Velocity() {
	Type.reset();
	Type.flip(VELOCITY);
	x = 0;
	y = 0;
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
