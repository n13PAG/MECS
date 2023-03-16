#pragma once

#include "..\Core\Component.h"

namespace MECS {
	struct Rotation : Component {
		float x;
		float y;
		float z;

		Rotation();
		Rotation(const float& x, const float& y, const float& z);
		void SetRotation(const Vector3& rotation);
	};
}

