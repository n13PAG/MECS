#pragma once

#include "MECS.h"

#include <set>

namespace MECS {
	class System {
	public:
		std::set<Entity> systemEntities;
		Signature systemSignature;

		void AddEntities(const std::vector<Entity>& entities) {
			for (const auto& e : entities) {
				systemEntities.insert(e);
			}
		}

		void AddEntity(Entity entity) {
			systemEntities.insert(entity);
		}

		void RemoveEntity(Entity entity, Signature entitySignature) {
			
		}
	};
}