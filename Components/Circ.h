#pragma once

#include "..\Core\Component.h"

namespace MECS {
	struct Circ: Component {
		float radius;

		Circ();
		Circ(const float& radius);
		void SetRadius(const float& radius);
	};
}
