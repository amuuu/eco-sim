#pragma once

#include "../EntityManagement/Entity.h"
#include "DecisionSystem.h"

namespace DecisionSystem
{
	
	class EntityWithStateOfMind : public EntityManagement::Entity, public StateOfMindContainer
	{
		CentralDecisionDriver cdd{};

		virtual void Init() override
		{
			cdd.Init();
		
			SetValueForStateOfMind(HUNGER, 12.f);
		}
		
		virtual void Update(EntityManagement::Tick tick) override
		{
			ChangeValueForStateOfMind(HUNGER, cdd.stateOfMindModels[HUNGER].autoUpdateAmount);

			if (tick % 100000 == 0)
				PrintAllStateOfMinds();
		}
	};
}