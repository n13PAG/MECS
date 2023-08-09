#include "scene_manager.h"

namespace MECS {
	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::SwitchScene(size_t scene_index)
	{
	}

	void SceneManager::InitManager()
	{
		current_scene_index_ = 0;
	}

	void SceneManager::RunScene(const float& dt)
	{
		IScene* current_scene = &GetCurrentScene();
		if (!current_scene->ShouldExit()) {
			current_scene->Start();
			current_scene->Update(dt);
			current_scene->Draw(dt);
		}
		else {
			LoadScene(current_scene->Exit());
		}
	}

	IScene& SceneManager::GetCurrentScene()
	{
		return *(scene_list_[current_scene_index_]);
	}

	void SceneManager::LoadScene(size_t scene_index)
	{
		current_scene_index_ = scene_index;

		// Load Transistion here
	}
}
