#include <iostream>

#include "raylib.h"

#include <stdint.h>
#include <vector>

#include "Core/Component.h"
#include "Core/ComponentManager.h"
#include "Core/EntityManager.h"
#include "Core/System.h"

#include "Components/Position.h"
#include "Components/Rect.h"
#include "Components/Renderable.h"
#include "Components/Velocity.h"

using namespace MECS;



std::vector<Entity> worldEntities;

EntityManager entityManager;

ComponentManager<Position> positionManager;
ComponentManager<Rect> rectManager;
ComponentManager<Renderable> renderableManager;
ComponentManager<Velocity> velocityManager;

struct PhysicsSystem : System {
	PhysicsSystem() {
		systemSignature.reset();
		systemSignature.flip(POSITION);
		systemSignature.flip(VELOCITY);
	}

	void Update(float dt);
};

void PhysicsSystem::Update(float dt) {
	for (auto const& entity : systemEntities) {
		
	}
}

int main() {

	InitWindow(1600, 900, "MECS");
	SetTargetFPS(60);

	int numberOfEntities = 200;

	for (Entity e = 0; e < numberOfEntities; e++) {
		e = entityManager.CreateEntity();
		Position* pos = positionManager.RegisterComponent(e);
		entityManager.UpdateSignature(e, POSITION);
		Rect* rect = rectManager.RegisterComponent(e);
		Renderable* render = renderableManager.RegisterComponent(e);
		Velocity* velocity = velocityManager.RegisterComponent(e);

		rect->SetSize({ 5, 5 });
		pos->SetPosition({ 0, e * (rect->height + 5) });
		render->color = RED;
		velocity->SetVelocity({ 500, 0 });

		worldEntities.push_back(e);
	}

	//Entity player = 0;

	//Position* pos_player = positionManager.RegisterComponent(player);
	//Rect* rect_player = rectManager.RegisterComponent(player);
	//Renderable* render_player = renderableManager.RegisterComponent(player);
	//Velocity* velocity_player = velocityManager.RegisterComponent(player);

	//pos_player->SetPosition({0, 0});
	//rect_player->SetSize({ 100, 80 });
	//render_player->color = RED;
	//velocity_player->SetVelocity({ 800, 0 });

	//std::cout << "Position: " << positionManager.GetComponent(player)->x << " " << positionManager.GetComponent(player)->y << "\n";
	//std::cout << "Rect: " << rectManager.GetComponent(player)->width << " " << rectManager.GetComponent(player)->height << "\n";
	//std::cout << "Color: " << renderableManager.GetComponent(player)->color.r << "\n";
	//std::cout << "Velocity: " << velocityManager.GetComponent(player)->x << " " << velocityManager.GetComponent(player)->y << "\n";

	while (!WindowShouldClose())
	{
		BeginDrawing();

		//pos_player->x += velocity_player->x * GetFrameTime();
		//pos_player->y += velocity_player->y * GetFrameTime();

		for (const auto& e : worldEntities) {
			Position* pos = positionManager.GetComponent(e);
			Velocity* vel = velocityManager.GetComponent(e);

			pos->x += vel->x * GetFrameTime();
			pos->y += vel->y * GetFrameTime();

			if (pos->x > GetScreenWidth()) {
				pos->x = 0;
			}
		}

		ClearBackground(RAYWHITE);

		for (const auto& e : worldEntities) {

			Position* pos = positionManager.GetComponent(e);
			Rect* rect = rectManager.GetComponent(e);
			Renderable* render = renderableManager.GetComponent(e);

			DrawRectangleRec({ pos->x, pos->y, rect->width, rect->height }, render->color);
		}
		
		//DrawRectangle(pos_player->x, pos_player->y, rect_player->width, rect_player->height, render_player->color);

		DrawFPS(0, 0);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}