#include "Rect.h"

using namespace MECS;

Rect::Rect() {
	Type.reset();
	Type.flip(RECT);
	width = 0;
	height = 0;
}

Rect::Rect(const float& width, const float& height) {
	Rect();
	this->width = width;
	this->height = height;
}

void Rect::SetSize(const Vector2& size) {
	width = size.x;
	width = size.y;
}
