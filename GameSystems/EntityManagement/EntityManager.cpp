#include "EntityManager.h"

using namespace EntityManagement;

ID EntityManager::EnqueueNewEntity(Entity* r)
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
	
	r->SetCreationTickStamp(HIRES_NOW);
	r->OnConstruct();
	r->InitComponents();

	entities[r->Id] = std::move(r);
	
	entitiesMutex.unlock();
}

Entity* EntityManager::GetEntityBasedOnID(const ID& id)
{
	return entities[id];
}

void EntityManager::DestroyEntity(ID id, bool extraCheckNotNeeded)
{
	entitiesMutex.lock();
		
	if (extraCheckNotNeeded || (entities.find(id) != entities.end()))
	{
		entities[id]->DestroyComponents();
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
	loopStartTimeStamp = std::chrono::high_resolution_clock::now();

	while (isLoopAwake)
	{
		// Initialize entities in queue
		entitiesQueueMutex.lock();
		while (!entitiesToInitialize.empty())
		{
			InitializeEntity(entitiesToInitialize.front());
			entitiesToInitialize.pop();
		}
		entitiesQueueMutex.unlock();

		// UpdateComponents alive entities
		entitiesMutex.lock();
		for (const auto& e : entities)
			e.second->UpdateComponents();
		entitiesMutex.unlock();

		// FixedUpdateComponents alive entities
		entitiesMutex.lock();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(HIRES_NOW - lastFixedUpdateTimestamp).count() >= FIXED_UPDATE_PERIOD_MILLIS)
		{
			lastFixedUpdateTimestamp = HIRES_NOW;
			
			for (const auto& e : entities)
			{
				e.second->FixedUpdateComponents();
			}
		}
		entitiesMutex.unlock();
	}
}

ID EntityManager::GetEntityIdBasedOnEntity(Entity* e)
{
	std::map<const ID, Entity*>::iterator targetIt{};
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

Tick EntityManagement::EntityManager::GetCurrentTick()
{
	return std::chrono::duration_cast<std::chrono::duration<double>>(HIRES_NOW - loopStartTimeStamp).count();
}
