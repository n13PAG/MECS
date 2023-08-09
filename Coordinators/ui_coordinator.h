#pragma once
#include "../Core/Coordinator.h"

#include "../Components/ui_element.h"
#include "../Components/transform.h"
#include "../Components/Rect.h"
#include "../Components/text.h"

namespace MECS {
	class UICoordinator : public Coordinator {
	public:
		UICoordinator() {
			RegisterComponentType<MECS::Transform>(kTransform);
			RegisterComponentType<MECS::Rect>(kRect);
			RegisterComponentType<MECS::DefaultText>(kText);
			RegisterComponentType<MECS::UIButton>(kUI_Button);
		}
	};
}