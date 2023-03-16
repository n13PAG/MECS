#include "Renderable.h"

using namespace MECS;

Renderable::Renderable() {
	Type.reset();
	Type.flip(RENDERABLE);
}

Renderable::Renderable(const Color& color) {
	Renderable();
	this->color = color;
}
