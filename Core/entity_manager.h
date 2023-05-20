#pragma once

#include "MECS.h"

#include <assert.h>
#include <queue>
#include <array>

namespace MECS {
	class EntityManager {
	private:

		std::queue<Entity> available_entites_;
		std::unordered_map<Entity, Signature> entity_signatures_map_;
		uint32_t active_entity_count = 0;

	public:
		EntityManager() {
			for (Entity e = 0; e < kMaxEntities; e++) {
				available_entites_.push(e);
			}
		}

		Entity CreateEntity() {
			// Triggers if : There are too many entities in the world
			assert(active_entity_count < kMaxEntities);

			Entity id = available_entites_.front();
			available_entites_.pop();

			Signature sig = 0;

			entity_signatures_map_.insert({ id, sig });

			active_entity_count++;

			return id;
		}

		void DestroyEntity(Entity entity_id) {
			// Triggers if : Entity doesn't exist
			assert(entity_signatures_map_.find(entity_id) != entity_signatures_map_.end());

			entity_signatures_map_.erase(entity_id);
			available_entites_.push(entity_id);
			active_entity_count--;
		}

		Signature GetSignature(Entity entity_id) {
			// Triggers if : Entity doesn't exist
			assert(entity_signatures_map_.find(entity_id) != entity_signatures_map_.end());

			return entity_signatures_map_[entity_id];
		}

		void UpdateSignature(Entity entity_id, ComponentType component_type) {
			Signature sig = GetSignature(entity_id) | component_type;
			entity_signatures_map_[entity_id] = sig;
		}
	};
}
