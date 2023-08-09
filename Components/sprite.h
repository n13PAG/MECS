#pragma once
#include "../Core/MECS.h"

namespace MECS {
	struct SpriteSQ {
		int index;
		Vector2 screen_size;
		Vector2 sprite_size;
		Color color;
	};

	struct Sprite : SpriteSQ {
		Vector2 texture_position;
	};
}