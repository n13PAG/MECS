#include <iostream>

#include "raylib.h"

int main() {

	InitWindow(1600, 800, "MECS");
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