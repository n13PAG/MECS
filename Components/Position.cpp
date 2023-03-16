
#include "Position.h"

using namespace MECS;

Position::Position() {
	Type.reset();
	Type.flip(POSITION);
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
