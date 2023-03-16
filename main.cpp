#include <iostream>

#include "raylib.h"

#include <stdint.h>
#include "Core/Component.h"
#include "Core/ComponentManager.h"

using namespace MECS;

int main() {


	InitWindow(160, 90, "MECS");
	SetTargetFPS(60);


	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}