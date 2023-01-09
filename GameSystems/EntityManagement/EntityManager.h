#pragma once

#include "Entity.h"

#include <map>


namespace EntityManagement
{

	typedef int EntityId;

	class EntityManager
	{
	public:
		
		EntityId AddNewEntity(Entity* r);
		Entity* GetEntityBasedOnID(const EntityId& id);

	private:
		std::map<const EntityId, Entity*> entities{};
		EntityId nextId{ 0 };

	};

}