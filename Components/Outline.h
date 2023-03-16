#pragma once

#include "..\Core\Component.h"

namespace MECS {
	struct Outline : Component {
		int outlineSize;
		Color outlineColor;

		Outline();
		Outline(int outlineSize, const Color& color);
	};
}
