#include "rotation.h"

namespace MECS {
	Rotation::Rotation() {
		type.set(kRotation);
		x = 0;
		y = 0;
		z = 0;
	}

	Rotation::Rotation(const float& x, const float& y, const float& z) {
		Rotation();
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Rotation::SetRotation(const Vector3& rotation) {
		x = rotation.x;
		y = rotation.y;
		z = rotation.z;
	}
}