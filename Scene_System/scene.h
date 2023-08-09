#pragma once

#include "raylib.h"

namespace MECS {
	const enum SceneList {
		kMenu,
		kGameplay,
		kSceneCount
	};

	class IScene
	{
	public:
		size_t GetSceneID();
		virtual void Start() = 0;
		virtual void Update(const float& dt) = 0;
		virtual void Draw(const float& dt) = 0;
		virtual size_t Exit() = 0;
		bool ShouldExit();

	protected:
		size_t scene_id_;
		float start_time_ = 0;
		float elapsed_time_ = 0;
		bool has_started_ = false;
		bool shoulde_exit_ = false;
	};
}
