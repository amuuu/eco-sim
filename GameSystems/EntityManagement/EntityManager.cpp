#include "EntityManager.h"

namespace EntityManagement
{

	EntityId EntityManager::EnqueueNewEntity(Entity* r)
	{
		r->Id = nextEntityId;

		entitiesQueueMutex.lock();
		entitiesToInitialize.push(r);
		entitiesQueueMutex.unlock();

		return nextEntityId++;
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

	void EntityManager::DestroyEntity(EntityId& id, bool extraCheckNotNeeded)
	{
		entitiesMutex.lock();
		
		if (extraCheckNotNeeded || (entities.find(id) != entities.end()))
		{
			entities[id]->OnDestroy();
			entities.erase(id);
		}
		
		entitiesMutex.unlock();
	}

	void EntityManager::DestroyEntity(Entity* entity)
	{
		if (auto eId = GetEntityIdBasedOnEntity(entity); eId != -1)
		{
			DestroyEntity(eId, true);
		}
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
			entitiesQueueMutex.unlock();

			// Update alive entities
			entitiesMutex.lock();
			for (const auto& e : entities)
				e.second->Update(currentTick);
			entitiesMutex.unlock();

			// FixedUpdate alive entities
			entitiesMutex.lock();
			if (std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - lastFixedUpdateTimestamp).count() >= FIXED_UPDATE_PERIOD)
			{
				lastFixedUpdateTimestamp = std::chrono::high_resolution_clock::now();
				currentFixedTick++; // this is not that accurate. It must be unique to each entity

				for (const auto& e : entities)
				{
					if (e.second->IsFixedUpdateActive())
						e.second->FixedUpdate(currentFixedTick);
				}
			}
			entitiesMutex.unlock();
		}
	}

	EntityId EntityManager::GetEntityIdBasedOnEntity(Entity* e)
	{
		std::map<const EntityId, Entity*>::iterator targetIt{};
		bool entityExists{ false };
		auto it = entities.begin();
		while (it != entities.end())
		{
			if ((*it).second == e)
			{
				targetIt = it;
				entityExists = true;
				break;
			}
		}

		if (entityExists)
			return (*it).first;
		else
			return -1;
	}

	void EntityManager::StartTheLoop()
	{
		mainLoopThread = std::make_unique<std::thread>(std::thread{ &EntityManager::MainEntityLoop, this });
	}

	void EntityManager::StopTheLoop()
	{
		isLoopAwake = false;
	}

	EntityManager::EntityManager(bool mustAutoStartLoopAfterInitialization) : autoStartLoop(mustAutoStartLoopAfterInitialization)
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