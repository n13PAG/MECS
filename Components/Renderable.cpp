#include "Renderable.h"

using namespace MECS;

Renderable::Renderable() {
	Type.reset();
	Type.flip(RENDERABLE);
	color = { 0, 0, 0, 0 };
}

Renderable::Renderable(const Color& color) {
	Renderable();
	this->color = color;
}
