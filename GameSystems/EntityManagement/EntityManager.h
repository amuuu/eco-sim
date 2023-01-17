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
#include <functional>
#include <future>
#include <thread>

#define FIXED_UPDATE_PERIOD 0.005


namespace EntityManagement
{

	class EntityManager
	{
	public:
		
		EntityId EnqueueNewEntity(Entity* r);
		Entity* GetEntityBasedOnID(const EntityId& id);
		
		void StartTheLoop();
		void StopTheLoop();
		
		EntityManager(bool mustAutoStartLoopAfterInitialization = true);
		~EntityManager();

	private:
		
		void InitializeEntity(Entity* r);
		void MainEntityLoop();

		std::map<const EntityId, Entity*> entities{}; // TODO: check if unordered_map is better for this case
		std::queue<Entity*> entitiesToInitialize{};
		std::mutex entitiesMutex{}, entitiesQueueMutex{};

		bool autoStartLoop{ true };

		EntityId nextEntityId{ 0 };
		
		std::unique_ptr<std::thread> mainLoopThread;

		std::atomic<Tick> currentTick{ 0 };
		std::atomic<Tick> currentFixedTick{ 0 };
		std::atomic_bool isLoopAwake{ true };

		std::chrono::high_resolution_clock::time_point lastFixedUpdateTimestamp{};
	};

}