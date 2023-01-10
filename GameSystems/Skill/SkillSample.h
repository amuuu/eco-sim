#pragma once

#include "SimpleEntityWithSkill.h"
#include "../EntityManagement/EntityManager.h"

namespace Samples
{
	namespace Skills
	{
		using namespace ::Skills;

		void Main()
		{
			EntityManager entityManager{ false };

			entityManager.EnqueueNewEntity(new SimpleEntityWithSkill{});

			entityManager.StartTheLoop();
		}
	}
}
