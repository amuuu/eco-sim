#pragma once

#include "Entity.h"

#include <map>


namespace EntityManagement
{

	typedef int EntityId;

	class EntityManager
	{
	public:
		EntityId AddNewEntity(Entity* r)
		{
			entities[nextId] = r;

			return nextId++;
		}

		Entity* GetEntityBasedOnID(const EntityId& id)
		{
			return entities[id];
		}

	private:
		std::map<const EntityId, Entity*> entities{};
		EntityId nextId{ 0 };

	};

}