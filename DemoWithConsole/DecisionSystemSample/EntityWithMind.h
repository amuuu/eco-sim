#pragma once

#include "GameSystems/EntityManagement/Entity.h"
#include "GameSystems/DecisionSystem/Mind.h"

#include <memory>
#include <iostream>
#include <variant>

using namespace DecisionSystem;

namespace DECISION_SYSTEM_SAMPLE
{
	
	class EntityWithMind : public EntityManagement::Entity
	{
		virtual void OnConstruct() override
		{
			this->AddComponent(new Mind{});
		}
		
	};
}