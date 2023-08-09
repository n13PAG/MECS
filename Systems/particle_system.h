#pragma once

#include "../Coordinators/particle_coordinator.h"

namespace MECS {
	class ParticleSystem : public System {
	public:
		ParticleSystem(ParticleCoordinator& particle_coordinator) {
			this->particle_coordinator = &particle_coordinator;
			AddToSystemSignature(kAdvParticle2D_Rect);
		}
		void Update(const float& dt);
	private:
		std::vector<Entity> particles_to_destroy_;
		ParticleCoordinator* particle_coordinator;
		void DestoryParticles();

		/// <summary>
/// Easing equation function for a quintic (t^5) easing in/out: 
/// acceleration until halfway, then deceleration.
/// </summary>
/// <param name="t">Current time in seconds.</param>
/// <param name="b">Starting value.</param>
/// <param name="c">Final value - Starting value</param>
/// <param name="d">Duration of animation.</param>
/// <returns>The correct value.</returns>
		float QuintEaseInOut(float t, float b, float c, float d)
		{
			if ((t /= d / 2) < 1)
				return c / 2 * t * t * t * t * t + b;
			return c / 2 * ((t -= 2) * t * t * t * t + 2) + b;
		}
	};
}
