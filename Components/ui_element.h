#pragma once
#include "../Core/MECS.h"

namespace MECS {

	enum UIStateFlags
	{
		kFlag_IsMouseOver = 1 << 0,
		kFlag_WasMouseClicked = 1 << 1,
		kFlag_LeftMouseHeld = 1 << 2,
		kFlag_IsDragging = 1 << 3
	};

	struct UIElement {
		unsigned int ui_state_flags;
	};

	enum UIButtonFlags {
		kFlag_ButtonPressed = 1 << 0,
		kFlag_ButtonSelected = 1 << 1
	};

	struct UIButton : UIElement{
		unsigned int button_state_flags;
	};
}