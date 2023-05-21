#pragma once

#include "MECS.h"

#include <assert.h>
#include <queue>
#include <array>
#include <set>

namespace MECS {
	using SystemSignature = Signature;
	
	class System {
	private:
		std::set<Entity> system_entities;
		SystemSignature system_signature;
	public:
		System() {

		}

		void SetSystemSignature(Signature sys_sig) {
			system_signature = sys_sig;
		}

		void AddToSystemSignature(ComponentType component_type) {
			system_signature = system_signature | component_type;
		}

		SystemSignature GetSystemSignature() {
			return system_signature;
		}

		void AddEntity(Entity entity_id) {
			system_entities.insert(entity_id);
		}

		void RemoveEntity(Entity entity_id) {
			system_entities.erase(entity_id);
		}

		bool EntitySignatureComparison(Signature entity_sig) {
			if ((entity_sig & system_signature) == system_signature) {
				return true;
			}
			else {
				return false;
			}
		}
	};
}