
#include "Position.h"

using namespace MECS;

Position::Position() {
	type.reset();
	type.flip(kPosition);
	x = 0;
	y = 0;
}

Position::Position(const float& x, const float& y) {
	Position();
	this->x = x;
	this->y = y;
}

void Position::SetPosition(const Vector2& position) {
	x = position.x;
	y = position.y;
}
