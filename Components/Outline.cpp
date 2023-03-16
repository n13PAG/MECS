#include "Outline.h"

using namespace MECS;

Outline::Outline() {
	Type.reset();
	Type.flip(OUTLINE);
	outlineSize = 0;
	outlineColor = { 0, 0, 0, 0 };
}

Outline::Outline(int outlineSize, const Color& color) {
	Outline();
	this->outlineSize = outlineSize;
	this->outlineColor = color;
}
