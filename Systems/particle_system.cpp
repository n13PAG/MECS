#include "particle_system.h"

#include <iostream>

namespace MECS {

	void ParticleSystem::Update(const float& dt) {
		//std::cout << dt << "\n";
		if (IsMouseButtonPressed(0)) {

			Vector3 particle_origin = { GetMousePosition().x, GetMousePosition().y, 0 };

			for (int i = 0; i < 20; i++) {
				Entity e = particle_coordinator->CreateEntity();
				particle_coordinator->AddComponent<Renderable>(e);
				

				if (e != -1) {
					auto& particle = particle_coordinator->AddComponent<AdvParticle2D_Rect>(e);

					particle.life_time = 2.8;
					particle.elapsed_time = 0;
					particle.position = particle_origin;
					particle.start_size = { 10, 10 };
					particle.start_color = BLUE;
					particle.color = particle.start_color;
					particle.start_rotation = { 0, 0, 0 };
					particle.start_velocity = { (float)GetRandomValue(-100, 100), (float)GetRandomValue(-100, 100), 0 };

					particle.end_size = { 0, 0 };
					particle.end_color = RED;
					particle.end_rotation = { 0, 0, 0 };
					particle.end_velocity = particle.start_velocity;

					particle.InitParticle();
				}
			}
		}

		if (system_entities.size() > 0) {
			for (auto const& e : system_entities) {
				auto& particle = particle_coordinator->GetComponent<AdvParticle2D_Rect>(e);

				// Countdown
				particle.elapsed_time += dt;

				if (particle.elapsed_time >= particle.life_time) {
					particle.elapsed_time = particle.life_time;
					particles_to_destroy_.push_back(e);
				}

				// Apply velocity
				particle.position.x += particle.velocity.x * dt;
				particle.position.y += particle.velocity.y * dt;

				// Apply change in size
				particle.size.x = QuintEaseInOut(particle.elapsed_time, particle.start_size.x, particle.end_size.x - particle.start_size.x, particle.life_time);
				particle.size.y = QuintEaseInOut(particle.elapsed_time, particle.start_size.y, particle.end_size.y - particle.start_size.y, particle.life_time);

				// Apply change in color
				particle.color.r = QuintEaseInOut(particle.elapsed_time, particle.start_color.r, particle.end_color.r - particle.start_color.r, particle.life_time);
				particle.color.b = QuintEaseInOut(particle.elapsed_time, particle.start_color.g, particle.end_color.g - particle.start_color.g, particle.life_time);
				particle.color.g = QuintEaseInOut(particle.elapsed_time, particle.start_color.b, particle.end_color.b - particle.start_color.b, particle.life_time);
				particle.color.a = QuintEaseInOut(particle.elapsed_time, particle.start_color.a, particle.end_color.a - particle.start_color.a, particle.life_time);

			}
		}

		DestoryParticles();
	}

	void ParticleSystem::DestoryParticles() {
		for (size_t i = 0; i < particles_to_destroy_.size(); i++) {
			particle_coordinator->DestroyEntity(particles_to_destroy_[i]);
		}


		if (particles_to_destroy_.size() > 0) {
			particles_to_destroy_.clear();
		}
	}
}