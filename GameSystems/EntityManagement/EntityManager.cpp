#include "EntityManager.h"

namespace EntityManagement
{

	EntityId EntityManager::EnqueueNewEntity(Entity* r)
	{
		r->Id = nextId;

		entitiesQueueMutex.lock();
		entitiesToInitialize.push(r);
		entitiesQueueMutex.unlock();

		return nextId++;
	}

	void EntityManager::InitializeEntity(Entity* r)
	{
		entitiesMutex.lock();
		entities[r->Id] = std::move(r);
		entitiesMutex.unlock();

		r->Init();
	}

	Entity* EntityManager::GetEntityBasedOnID(const EntityId& id)
	{
		return entities[id];
	}
	
	void EntityManager::MainEntityLoop()
	{
		while (isLoopAwake)
		{
			currentTick++;
			
			// Initialize entities in queue
			entitiesQueueMutex.lock();
			while (!entitiesToInitialize.empty())
			{
				InitializeEntity(entitiesToInitialize.front());
				entitiesToInitialize.pop();
			}
			entitiesMutex.unlock();

			// Update alive entities
			entitiesMutex.lock();
			for (const auto& e : entities)
				e.second->Update(currentTick);
			entitiesMutex.unlock();

		}
	}

	void EntityManager::StartTheLoop()
	{
		mainLoopThread = std::make_unique<std::thread>(std::thread{ &EntityManager::MainEntityLoop, this });
	}

	EntityManager::EntityManager(bool mustAutoStartLoopAfterInitialization) : mustAutoStartLoopAfterInitialization(mustAutoStartLoopAfterInitialization)
	{
		// Proly other stuff too

		if (mustAutoStartLoopAfterInitialization)
			StartTheLoop();
	}
	
	EntityManager::~EntityManager()
	{
		mainLoopThread->join();
	}
}