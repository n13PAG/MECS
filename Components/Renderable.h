#pragma once

#include "..\Core\Component.h"

namespace MECS {
	struct Renderable : Component {
		Color color;

		Renderable();
		Renderable(const Color& color);
	};
}
