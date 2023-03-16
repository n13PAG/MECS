#include <iostream>

#include "raylib.h"

#include <stdint.h>
#include "Core/Component.h"
#include "Core/ComponentManager.h"

#include "Components/Position.h"
#include "Components/Rect.h"
#include "Components/Renderable.h"
#include "Components/Velocity.h"

using namespace MECS;

int main() {

	ComponentManager<Position> positionManager;
	ComponentManager<Rect> rectManager;
	ComponentManager<Renderable> renderableManager;
	ComponentManager<Velocity> velocityManager;


	InitWindow(1600, 900, "MECS");
	SetTargetFPS(60);

	Entity player = 0;

	Position* pos_player = positionManager.RegisterComponent(player);
	Rect* rect_player = rectManager.RegisterComponent(player);
	Renderable* render_player = renderableManager.RegisterComponent(player);
	Velocity* velocity_player = velocityManager.RegisterComponent(player);

	pos_player->SetPosition({0, 0});
	rect_player->SetSize({ 100, 80 });
	render_player->color = RED;
	velocity_player->SetVelocity({ 800, 0 });

	std::cout << "Position: " << positionManager.GetComponent(player)->x << " " << positionManager.GetComponent(player)->y << "\n";
	std::cout << "Rect: " << rectManager.GetComponent(player)->width << " " << rectManager.GetComponent(player)->height << "\n";
	std::cout << "Color: " << renderableManager.GetComponent(player)->color.r << "\n";
	std::cout << "Velocity: " << velocityManager.GetComponent(player)->x << " " << velocityManager.GetComponent(player)->y << "\n";

	while (!WindowShouldClose())
	{
		BeginDrawing();

		pos_player->x += velocity_player->x * GetFrameTime();
		pos_player->y += velocity_player->y * GetFrameTime();

		if (pos_player->x > GetScreenWidth()) {
			pos_player->x = 0;
		}

		ClearBackground(RAYWHITE);

		DrawRectangle(pos_player->x, pos_player->y, rect_player->width, rect_player->height, render_player->color);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}