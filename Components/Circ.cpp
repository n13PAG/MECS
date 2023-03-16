#include "Circ.h"

using namespace MECS;

Circ::Circ() {
	Type.reset();
	Type.flip(CIRC);
	radius = 0;
}

Circ::Circ(const float& radius) {
	Circ();
	this->radius = radius;
}

void Circ::SetRadius(const float& radius) {
	this->radius = radius;
}
