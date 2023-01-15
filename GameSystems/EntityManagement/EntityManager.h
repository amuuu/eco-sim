#pragma once

#include "Entity.h"
#include "EntityGlobals.h"

#include <map>
#include <atomic>
#include <queue>
#include <thread>
#include <memory>
#include <mutex>
#include <chrono>
#include <ctime>
#include <ratio>

#define FIXED_UPDATE_PERIOD 0.005


namespace EntityManagement
{

	class EntityManager
	{
	public:
		
		EntityId EnqueueNewEntity(Entity* r);
		void InitializeEntity(Entity* r);
		Entity* GetEntityBasedOnID(const EntityId& id);
		
		void MainEntityLoop();
		void StartTheLoop();
		void StopTheLoop();
		
		EntityManager(bool mustAutoStartLoopAfterInitialization = true);
		~EntityManager();

	private:
		std::map<const EntityId, Entity*> entities{};
		std::queue<Entity*> entitiesToInitialize{};
		std::mutex entitiesMutex{}, entitiesQueueMutex{};

		bool mustAutoStartLoopAfterInitialization{ true };

		EntityId nextId{ 0 };
		
		std::unique_ptr<std::thread> mainLoopThread;

		std::atomic <Tick> currentTick{ 0 };
		std::atomic <Tick> currentFixedTick{ 0 };
		std::atomic_bool isLoopAwake{ true };
		
		std::chrono::high_resolution_clock::time_point lastFixedUpdateTimestamp{};
	};

}