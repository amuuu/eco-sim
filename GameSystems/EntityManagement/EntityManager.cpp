#include "EntityManager.h"

namespace EntityManagement
{

	EntityId EntityManager::EnqueueNewEntity(Entity* r)
	{
		r->Id = nextId;

		entitiesToInitialize.push(r);

		return nextId++;
	}

	void EntityManager::InitializeEntity(Entity* r)
	{
		entities[r->Id] = std::move(r);
		r->Init();
	}

	Entity* EntityManager::GetEntityBasedOnID(const EntityId& id)
	{
		return entities[id];
	}
	
	void EntityManager::MainEntityLoop(EntityManager& thisObject)
	{
		while (thisObject.isLoopAwake)
		{
			thisObject.currentTick++;
			
			// Initialize entities in queue
			thisObject.entitiesQueueMutex.lock();
			while (!thisObject.entitiesToInitialize.empty())
			{
				thisObject.InitializeEntity(thisObject.entitiesToInitialize.front());
				thisObject.entitiesToInitialize.pop();
			}
			thisObject.entitiesQueueMutex.unlock();

			// Update alive entities
			thisObject.entitiesMutex.lock();
			for (const auto& e : thisObject.entities)
				e.second->Update(thisObject.currentTick);
			thisObject.entitiesMutex.unlock();

		}
	}

	void EntityManager::StartTheLoop()
	{
		mainLoopThread = std::make_unique<std::thread>(new std::thread{ &EntityManager::MainEntityLoop, this });
	}

	EntityManager::EntityManager(bool mustAutoStartLoopAfterInitialization) : mustAutoStartLoopAfterInitialization(mustAutoStartLoopAfterInitialization)
	{
		// Proly other stuff too

		if (mustAutoStartLoopAfterInitialization)
			StartTheLoop();
	}
}