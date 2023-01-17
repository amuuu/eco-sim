#pragma once

#include "../GameSystems/GameSystems/EntityManagement/EntityManager.h"
#include "SimpleDumbEntity.h"
using namespace EntityManagement;

namespace ENTITY_MANAGEMENT_SAMPLE
{
	static void EXECUTE()
	{
		EntityManager entityManager{ false };
			
		entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
		entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
		entityManager.StartTheLoop();
		entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
		entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
	}
}
