#pragma once

#include "MECS.h"

#include <assert.h>
#include <queue>
#include <array>

namespace MECS {
	struct EntityManager {
	private:
		std::queue<Entity> mAvailableEntities;
		std::array<Signature, MAX_ENTITIES> mEntitySignatures;
		uint32_t mActiveEntityCount = 0;
	public:
		EntityManager() {
			for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
				mAvailableEntities.push(entity);
			}
		}

		Entity CreateEntity() {
			// Triggers if : There are too many entities in the world
			assert(mActiveEntityCount < MAX_ENTITIES);

			Entity id = mAvailableEntities.front();
			mAvailableEntities.pop();

			mActiveEntityCount++;

			return id;
		}

		Entity CreateEntity(Signature signature) {
			// Triggers if : There are too many entities in the world
			assert(mActiveEntityCount < MAX_ENTITIES);

			Entity id = mAvailableEntities.front();
			mAvailableEntities.pop();

			mActiveEntityCount++;

			SetSignature(id, signature);

			return id;
		}

		void DestoryEntity(Entity entity) {
			// Triggers if : There are too many entities in the world
			assert(entity < MAX_ENTITIES);

			mAvailableEntities.push(entity);
			
			// TODO : Find a way to delegate the removal of all the components

			mActiveEntityCount++;
		}

		void SetSignature(Entity entity, Signature signature) {
			// Triggers if : There are too many entities in the world
			assert(entity < MAX_ENTITIES);

			mEntitySignatures[entity] = signature;
		}

		void UpdateSignature(Entity entity, Signature componentSignature) {
			
			// TODO does this even work?
			mEntitySignatures[entity] = mEntitySignatures[entity] | componentSignature;
		}

		Signature GetSignature(Entity entity) {
			// Triggers if : There are too many entities in the world
			assert(entity < MAX_ENTITIES);

			return mEntitySignatures[entity];
		}
	};
}
