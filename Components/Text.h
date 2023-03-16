#pragma once

#include "..\Core\Component.h"

namespace MECS {
	struct Text : Component {
		const char* text;
		int fontSize;
		Color fontColor;

		Text();
		Text(const char* text, int fontSize, const Color& color);
	};
}