#pragma once

#include "../EntityManagement/Entity.h"

#include "MindVarModelsContainer.h"

#include <memory>

namespace DecisionSystem
{
	
	class EntityWithMindVar : public EntityManagement::Entity, public MindVarContainer
	{

		virtual void Init() override
		{
			//SetCentralDecisionDriver(cdd);


			SetValueForMindVar(HUNGER, 12.f);
		}
		
		virtual void Update(EntityManagement::Tick tick) override
		{
			/*if (tick % 100000 == 0)
			{
				UpdateMindVars();
				PrintAllMindVars();
			}*/
		}
	};
}