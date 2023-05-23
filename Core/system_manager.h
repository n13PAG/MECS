#pragma once

#include "system.h"

#include <assert.h>
#include <array>
#include <memory>
#include <unordered_map>
#include <set>

namespace MECS {
	class SystemManager {
	private:
		std::vector<std::shared_ptr<System>> systems_;
		std::unordered_map<Entity, Signature> updated_entities_;
	public:

		void RegisterSystem(std::shared_ptr<System> system) {
			systems_.push_back(system);
		}

		void AddEntityToUpdate(Entity entity_id, Signature sig) {
			updated_entities_.insert({ entity_id, sig });
 		}

		void ReassignEntity(Entity entity_id, Signature new_sig) {
			for (auto sys : systems_) {
				if (sys->EntitySignatureComparison(new_sig)) {
					sys->AddEntity(entity_id);
				}
				else {
					sys->RemoveEntity(entity_id);
				}
			}

			updated_entities_.erase(entity_id);
		}

		void ReassignAllEntities() {
			for (auto e : updated_entities_) {
				ReassignEntity(e.first, e.second);
				updated_entities_.erase(e.first);
			}
		}
	};
}