#pragma once

#include "../EntityManagement/Entity.h"

#include "EntityMindVarContainer.h"

#include <memory>

namespace DecisionSystem
{
	
	class EntityWithMindVar : public EntityManagement::Entity, public EntityMindVarContainer
	{

		virtual void Init() override
		{
			SetValueForMindVar(HUNGER, 12.f);
			SetValueForMindVar(MORALE, 35.f);
		}
		
		virtual void Update(EntityManagement::Tick tick) override
		{
			if (tick % 100000 == 0)
			{
				UpdateMindVars();
				PrintAllMindVars();
			}
		}
	};
}