#include <iostream>

#include "raylib.h"

#include <stdint.h>
#include <vector>
#include <string>

#include "Core/coordinator.h"
#include "Core/particle_coordinator.h"


using namespace MECS;



ParticleCoordinator particle_coordinator;

class ParticleSystem : public System {
public:
	void Update(float dt) {
		if (IsMouseButtonPressed(0)) {

			Vector3 particle_origin = { GetMousePosition().x, GetMousePosition().y, 0 };

			for (int i = 0; i < 20; i++) {
				Entity e = particle_coordinator.CreateEntity();

				if (e != -1) {
					auto& particle = particle_coordinator.AddComponent<AdvParticle2D_Rect>(e);
					
					particle.life_time = 1.8;
					particle.elapsed_time = 0;
					particle.position = particle_origin;
					particle.start_size = { 10, 10 };
					particle.start_color = PURPLE;
					particle.start_rotation = { 0, 0, 0 };
					particle.start_velocity = { (float)GetRandomValue(-100, 100), (float)GetRandomValue(-100, 100), 0 };

					particle.end_size = { 0, 0 };
					particle.end_color = RED;
					particle.end_rotation = { 0, 0, 0 };
					particle.end_velocity = particle.start_velocity;
			
					particle.InitParticle();
				}
				else {
					std::cout << "Entity limit reached!!";
				}
			}
		}


		if (system_entities.size() > 0) {
			for (auto const& e : system_entities) {
				auto& particle = particle_coordinator.GetComponent<AdvParticle2D_Rect>(e);

				// Countdown
				particle.elapsed_time += dt;

				if (particle.elapsed_time >= particle.life_time) {
					particles_to_destroy.push_back(e);
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

		for (size_t i = 0; i < particles_to_destroy.size(); i++) {
			particle_coordinator.DestroyEntity(particles_to_destroy[i]);
		}

		if (particles_to_destroy.size() > 0) {
			particles_to_destroy.clear();
		}
	}
private:
	std::vector<Entity> particles_to_destroy;


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

class Renderer : public System {
public:
	void Update(float dt) {
		if (system_entities.size() > 0) {
			for (auto const& e : system_entities) {
				auto& particle = particle_coordinator.GetComponent<AdvParticle2D_Rect>(e);

				DrawRectangle(particle.position.x, particle.position.y, particle.size.x, particle.size.y, particle.color);
			}
		}
	}
};

int main() {

	std::shared_ptr<ParticleSystem> particle_system = std::make_shared<ParticleSystem>();
	particle_coordinator.RegisterSystem(particle_system);
	particle_coordinator.AddToSystemSignature<AdvParticle2D_Rect>(particle_system);

	std::shared_ptr<Renderer> particle_render_system = std::make_shared<Renderer>();
	particle_coordinator.RegisterSystem(particle_render_system);
	particle_coordinator.AddToSystemSignature<AdvParticle2D_Rect>(particle_render_system);

	InitWindow(1600, 900, "MECS");
	SetTargetFPS(60);

	float life_time = 1.2;
	float counter = 0;

	Vector3 particle_pos = { 0, 0, 0 };

	while (!WindowShouldClose())
	{
		particle_system->Update(GetFrameTime());

		BeginDrawing();

		ClearBackground(RAYWHITE);

		particle_render_system->Update(GetFrameTime());

		DrawFPS(0, 0);

		std::string particle_count = std::to_string(particle_system->system_entities.size());
		DrawText(particle_count.c_str(), 10, 10, 20, RED);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}