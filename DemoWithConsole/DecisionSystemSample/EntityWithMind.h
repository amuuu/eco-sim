#pragma once

#include "GameSystems/EntityManagement/Entity.h"
#include "GameSystems/DecisionSystem/Mind.h"
#include "GameSystems/GeneralComponents/Timer.h"

#include <memory>
#include <iostream>
#include <variant>

using namespace GeneralComponents;
using namespace DecisionSystem;

namespace DECISION_SYSTEM_SAMPLE
{
	
	class EntityWithMind : public EntityManagement::Entity
	{
		virtual void OnConstruct() override
		{
			this->AddComponent(new Mind{});
			this->AddComponent(new Timer{});

			auto* timer = this->GetComponent<GeneralComponents::Timer>();
			//auto* timer = dynamic_cast<Timer*>(this->GetComponent(2));
			
			if (timer != nullptr)
			{
				//timer->Start();
			}
		}
		
	};
}