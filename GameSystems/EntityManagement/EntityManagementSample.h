#pragma once

#include "EntityManager.h"
#include "SimpleDumbEntity.h"

namespace Samples
{
	namespace EntityManagement
	{
		using namespace ::EntityManagement;

		void Main()
		{
			EntityManager entityManager{ false };
			
			entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
			entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
			entityManager.StartTheLoop();
			entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
			entityManager.EnqueueNewEntity(new SimpleDumbEntity{});

		}
	}
}
