#include <iostream>

#include "raylib.h"

#include <stdint.h>
#include <vector>
#include <string>
#include <memory>

#include "Systems/particle_system.h"
#include "Systems/ui_system.h"


using namespace MECS;


ParticleCoordinator particle_coordinator;
UICoordinator ui_coordinator;

class ParticleRenderer : public System {
public:
	ParticleRenderer() {
		AddToSystemSignature(kRenderable);
	}
	void Render() {
		if (system_entities.size() > 0) {
			for (auto const& e : system_entities) {
				auto& renderable = particle_coordinator.GetComponent<Renderable>(e);
				auto& particle = particle_coordinator.GetComponent<AdvParticle2D_Rect>(e);

				DrawRectangle(particle.position.x, particle.position.y, particle.size.x, particle.size.y, particle.color);
				
			}
		}
	}
};

int main() {

	std::shared_ptr<ParticleSystem> particle_system = std::make_shared<ParticleSystem>(particle_coordinator);
	std::shared_ptr<ParticleRenderer> renderer_system = std::make_shared<ParticleRenderer>();
	particle_coordinator.RegisterSystem(particle_system);
	particle_coordinator.RegisterSystem(renderer_system);

	std::shared_ptr<UISystem> ui_system = std::make_shared<UISystem>(ui_coordinator);
	ui_coordinator.RegisterSystem(ui_system);


	InitWindow(1600, 900, "MECS");
	SetTargetFPS(60);

	ui_system->SetupUI();
	Color textCol = BLACK;

	while (!WindowShouldClose())
	{

		ui_system->Update(GetFrameTime());

		BeginDrawing();

		ClearBackground(RAYWHITE);

		renderer_system->Render();
		ui_system->Draw();
		DrawFPS(0, 0);
		//DrawText(std::to_string(particle_system->system_entities.size()).c_str(), 0, 20, 20, RED);

		//DrawText(std::to_string(GetFrameTime()).c_str(), 0, 40, 20, BLACK);

		EndDrawing();

		float dt = GetFrameTime();
		if (dt > 1) {
			std::cout << dt << "\n";
		}
		particle_system->Update(dt);
	}

	CloseWindow();

	return 0;
}