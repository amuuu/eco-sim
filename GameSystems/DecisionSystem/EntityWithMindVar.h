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
			if (tick % 100000 == 0) // this is ugly ticks are too fast for the frequency by which we want the vars to be update. we neeed a cleaner way
			{
				UpdateMindVars();
				PrintAllMindVars();
			}
		}

		virtual void FixedUpdate(EntityManagement::Tick fixedTick) override
		{

		}
	};
}