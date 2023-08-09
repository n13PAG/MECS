#pragma once

#include "../Coordinators/ui_coordinator.h"

namespace MECS {
	class UISystem : public System {
	public:
		UISystem(UICoordinator& ui_coordinator) {
			this->ui_coordinator = &ui_coordinator;
			AddToSystemSignature(kTransform);
			AddToSystemSignature(kRect);
			AddToSystemSignature(kText);
			AddToSystemSignature(kUI_Button);
		}

		void SetupUI() {
			Vector2 start_pos = { GetScreenWidth() / 2, GetScreenHeight() / 2 };
			start_pos.x -= 100;
			start_pos.y -= 400;

			for (int i = 0; i < 3; i++) {
				Entity btn = CreateButton();

				SetupButtonTransform(btn, { start_pos.x, start_pos.y + (100 * i)});
				SetupButtonRect(btn, { 200, 100 }, BLUE);
				SetupButtonText(btn, "Button " + std::to_string(i), BLACK, 20);
			}
		}

		void Update(const float& dt) {
			if (system_entities.size() > 0) {
				for (auto const& e : system_entities) {
					UpdateButtonState(e);
					UpdateButton(e);
				}
			}
		}

		void Draw() {
			if (system_entities.size() > 0) {
				for (auto const& e : system_entities) {
					MECS::Transform* transform = &(ui_coordinator->GetComponent<Transform>(e));
					MECS::Rect* rect = &(ui_coordinator->GetComponent<Rect>(e));
					MECS::DefaultText* text_comp = &(ui_coordinator->GetComponent<DefaultText>(e));
					//DrawRectangle(transform->position.x, transform->position.y, rect->width, rect->height, rect->color);
					DrawRectanglePro({ transform->position.x, transform->position.y, rect->width, rect->height }, { 0, 0 }, 0, rect->color);
					DrawText(text_comp->text.c_str(), transform->position.x, transform->position.y, text_comp->font_size, text_comp->color);
				}
			}
		}
	private:
		UICoordinator* ui_coordinator;

		Entity CreateButton() {
			Entity e = ui_coordinator->CreateEntity();

			ui_coordinator->AddComponent<MECS::Transform>(e);
			ui_coordinator->AddComponent<MECS::Rect>(e);
			ui_coordinator->AddComponent<MECS::DefaultText>(e);
			ui_coordinator->AddComponent<MECS::UIButton>(e);

			return e;
		}

		void SetupButtonTransform(Entity e, Vector2 position) {
			MECS::Transform* transform = &(ui_coordinator->GetComponent<Transform>(e));
			transform->position.x = position.x;
			transform->position.y = position.y;
			transform->rotation = 0;
		}

		void SetupButtonRect(Entity e, Vector2 size, Color color) {
			MECS::Rect* rect = &(ui_coordinator->GetComponent<Rect>(e));
			rect->SetSize(size);
			rect->color = color;
		}

		void SetupButtonText(Entity e, std::string text, Color text_color, float font_size) {
			MECS::DefaultText* text_comp = &(ui_coordinator->GetComponent<DefaultText>(e));
			text_comp->text = text;
			text_comp->color = text_color;
			text_comp->font_size = font_size;
		}

		void UpdateButtonState(Entity e) {
			MECS::Transform* transform = &(ui_coordinator->GetComponent<MECS::Transform>(e));
			MECS::Rect* rect = &(ui_coordinator->GetComponent<MECS::Rect>(e));
			MECS::DefaultText* text = &(ui_coordinator->GetComponent<MECS::DefaultText>(e));
			MECS::UIButton* button = &(ui_coordinator->GetComponent<MECS::UIButton>(e));

			Vector2 mouse_pos = GetMousePosition();

			if (CheckCollisionPointRec(mouse_pos, { transform->position.x, transform->position.y, rect->width, rect->height })) {
				button->ui_state_flags |= kFlag_IsMouseOver;
			}
			else {
				button->ui_state_flags &= ~kFlag_IsMouseOver;
			}

			if (button->ui_state_flags & kFlag_IsMouseOver) {
				if (IsMouseButtonPressed(0)) {
					button->button_state_flags ^= kFlag_ButtonPressed;
				}
			}
		}

		void UpdateButton(Entity e) {
			MECS::Transform* transform = &(ui_coordinator->GetComponent<MECS::Transform>(e));
			MECS::Rect* rect = &(ui_coordinator->GetComponent<MECS::Rect>(e));
			MECS::DefaultText* text = &(ui_coordinator->GetComponent<MECS::DefaultText>(e));
			MECS::UIButton* button = &(ui_coordinator->GetComponent<MECS::UIButton>(e));

			if (button->ui_state_flags & kFlag_IsMouseOver) {
				rect->color = SKYBLUE;
				//transform->position.y = ((float)GetScreenHeight()/2) + 5;
			}
			else {
				rect->color = BLUE;
				//transform->position.y = ((float)GetScreenHeight() / 2);
			}

			if (button->button_state_flags & kFlag_ButtonPressed) {
				rect->color = RED;
			}
		}
	};
}
