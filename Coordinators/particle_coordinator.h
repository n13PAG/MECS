#pragma once

#include "../Core/Coordinator.h"

#include "../Components/particle.h"
#include "../Components/Renderable.h"

namespace MECS {
	class ParticleCoordinator : public Coordinator {
	public:
		ParticleCoordinator() {
			Init();
		}

		void Init() {
			//RegisterComponentType<AdvParticle2D_Rect>();
			RegisterComponentType<AdvParticle2D_Rect>(kAdvParticle2D_Rect);
			RegisterComponentType<Renderable>(kRenderable);
		}
	};
}