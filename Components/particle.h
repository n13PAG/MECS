#pragma once

#include "../Core/MECS.h"

namespace MECS {
	struct Particle {
		Vector3 position;
		Vector3 direction;
		Vector3 rotation;
		Vector3 velocity;
		Color color;
		float life_time;
		float elapsed_time;
	};

	struct AdvParticle : Particle {
		Vector3 start_rotation;
		Vector3 end_rotation;
		Vector3 start_velocity;
		Vector3 end_velocity;
		Color start_color;
		Color end_color;
	};
#pragma region 2D
	struct Particle2D_Rect : Particle {
		Vector2 size;
	};

	struct AdvParticle2D_Rect : AdvParticle {
		Vector2 size;
		Vector2 start_size;
		Vector2 end_size;

		void InitParticle() {
			rotation = start_rotation;
			velocity = start_velocity;
			color = start_color;
			size = start_size;
		}
	};

	struct ParticleTex {
		Vector2 direction;
		float life_time;
		float elapsed_time;
	};

#pragma endregion


}

