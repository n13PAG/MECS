#include "scene.h"

namespace MECS {
	size_t IScene::GetSceneID()
	{
		return scene_id_;
	}

	bool IScene::ShouldExit()
	{
		return shoulde_exit_;
	}
}
