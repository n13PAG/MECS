#pragma once
#include "../Core/MECS.h"

#include <string>

namespace MECS {
	struct DefaultText {
		std::string text;
		float font_size;
		Color color;
	};

	struct Text {
		std::string text;
		Font font;
		float font_size;
		float spacing;
		Color color;
	};

	Vector2 GetTextSize(const Text& text) {
		return MeasureTextEx(text.font, text.text.c_str(), text.font_size, text.spacing);
	}
}