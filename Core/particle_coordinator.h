#pragma once

#include "coordinator.h"

#include "../Components/particle.h"

namespace MECS {
	class ParticleCoordinator : public Coordinator {
	public:
		ParticleCoordinator() {
			Init();
		}

		void Init() {
			RegisterComponentType<AdvParticle2D_Rect>();
		}
	};
}