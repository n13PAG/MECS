#include <iostream>

#include "raylib.h"

#include <stdint.h>
#include <vector>

#include "Core/coordinator.h"


using namespace MECS;



Coordinator coordinator;

int main() {

	std::shared_ptr<System> testSystem;
	testSystem = std::make_shared<System>();

	InitWindow(1600, 900, "MECS");
	SetTargetFPS(60);

	Entity e = coordinator.CreateEntity();
	coordinator.AddComponent<Position>(e);

	coordinator.GetComponent<Position>(e).x = 20;
	std::cout << coordinator.GetComponent<Position>(e).x << std::endl;
	std::cout << coordinator.GetSignature(e) << std::endl;
	coordinator.RemoveComponent<Position>(e);
	std::cout << coordinator.GetSignature(e) << std::endl;
	coordinator.DestroyEntity(e);

	coordinator.Debug({ typeid(Position).name(), typeid(Rotation).name() });

	coordinator.RegisterSystem(testSystem);
	coordinator.AddToSystemSignature<Position>(testSystem);
	coordinator.AddToSystemSignature<Rotation>(testSystem);


	std::cout << testSystem->GetSystemSignature() << std::endl;

	while (!WindowShouldClose())
	{
		BeginDrawing();


		ClearBackground(RAYWHITE);


		DrawFPS(0, 0);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}