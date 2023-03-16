#include "Text.h"

using namespace MECS;

Text::Text() {
	Type.reset();
	Type.flip(TEXT);
	text = "Unintialized text component";
	fontSize = 0;
	fontColor = { 0, 0, 0, 0 };
}

Text::Text(const char* text, int fontSize, const Color& color) {
	Text();
	this->text = text;
	this->fontSize = fontSize;
	this->fontColor = color;
}
