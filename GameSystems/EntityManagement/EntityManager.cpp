#include "EntityManager.h"

namespace EntityManagement
{

	EntityId EntityManager::AddNewEntity(Entity* r)
	{
		entities[nextId] = r;

		return nextId++;
	}

	Entity* EntityManager::GetEntityBasedOnID(const EntityId& id)
	{
		return entities[id];
	}
}