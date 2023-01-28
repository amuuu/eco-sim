#pragma once

#include "GameSystems/EntityManagement/Entity.h"
#include "GameSystems/DecisionSystem/Mind.h"
using namespace DecisionSystem;

#include <memory>
#include <iostream>

namespace DECISION_SYSTEM_SAMPLE
{
	
	class EntityWithMindVar : public EntityManagement::Entity
	{

		virtual void OnConstruct() override
		{
			this->AddComponent(new Mind{});
		}
		
	};
}