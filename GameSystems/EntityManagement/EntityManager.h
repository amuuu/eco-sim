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

#define FIXED_UPDATE_PERIOD_MILLIS 100


namespace EntityManagement
{

	class EntityManager
	{
	public:
		
		ID EnqueueNewEntity(Entity* r);
		Entity* GetEntityBasedOnID(const ID& id);
		
		void DestroyEntity(ID id, bool extraCheckNotNeeded = true);
		void DestroyEntity(Entity* entity);

		void StartTheLoop();
		void StopTheLoop();
		
		EntityManager(bool mustAutoStartLoopAfterInitialization = true);
		~EntityManager();

		////////// tmp
		
		std::map<const ID, Entity*>* GetAllEntities() { return &entities; }
		
		Tick GetCurrentTick();
		
		//////////////

	private:
		
		void InitializeEntity(Entity* r);
		void MainEntityLoop();

		ID GetEntityIdBasedOnEntity(Entity* e);

		std::map<const ID, Entity*> entities{}; // TODO: check if unordered_map is better for this case
		std::queue<Entity*> entitiesToInitialize{};
		std::mutex entitiesMutex{}, entitiesQueueMutex{};

		bool autoStartLoop{ true };

		ID nextEntityId{ 0 };
		
		std::unique_ptr<std::thread> mainLoopThread;

		std::atomic_bool isLoopAwake{ true };

		HiResTimeStamp lastFixedUpdateTimestamp{};
		HiResTimeStamp loopStartTimeStamp{};
	};

}