#pragma once

#include "GameSystems/EntityManagement/Entity.h"
#include "GameSystems/DecisionSystem/Mind.h"
#include "GameSystems/GeneralComponents/Timer.h"

#include <memory>
#include <iostream>

namespace DECISION_SYSTEM_SAMPLE
{
	
	class EntityWithMind : public EntityManagement::Entity
	{
		virtual void OnConstruct() override
		{
			this->AddComponent(new DecisionSystem::Mind{});
			this->AddComponent(new GeneralComponents::Timer{});
		}
		
	};
}