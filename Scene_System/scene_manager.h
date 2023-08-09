#pragma once

#include <vector>
#include <memory>

#include "scene.h"

namespace MECS {
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();
		void SwitchScene(size_t scene_index);
		void InitManager();
		void RunScene(const float& dt);

	private:
		size_t current_scene_index_ = 0;
		std::vector<std::shared_ptr<IScene>> scene_list_;
		IScene& GetCurrentScene();
		void LoadScene(size_t scene_index);
	};
}

