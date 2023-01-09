#pragma once

#include "Entity.h"
#include "EntityGlobals.h"

#include <map>
#include <atomic>
#include <queue>
#include <thread>
#include <memory>
#include <mutex>

namespace EntityManagement
{

	class EntityManager
	{
	public:
		
		EntityId EnqueueNewEntity(Entity* r);
		void InitializeEntity(Entity* r);
		Entity* GetEntityBasedOnID(const EntityId& id);
		
		void MainEntityLoop(EntityManager& thisObject);
		void StartTheLoop();
		EntityManager(bool mustAutoStartLoopAfterInitialization);

	private:
		std::map<const EntityId, Entity*> entities{};
		std::queue<Entity*> entitiesToInitialize{};
		std::mutex entitiesMutex, entitiesQueueMutex;

		bool mustAutoStartLoopAfterInitialization{ true };

		EntityId nextId{ 0 };
		
		std::unique_ptr<std::thread> mainLoopThread;

		std::atomic <Tick> currentTick{ 0 };
		std::atomic_bool isLoopAwake{ true };
	};

}