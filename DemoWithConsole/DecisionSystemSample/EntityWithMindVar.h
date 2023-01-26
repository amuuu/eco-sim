#pragma once

#include "GameSystems/EntityManagement/Entity.h"
#include "GameSystems/DecisionSystem/EntityBrain.h"
using namespace DecisionSystem;

#include <memory>

namespace DECISION_SYSTEM_SAMPLE
{
	
	class EntityWithMindVar : public EntityManagement::Entity, public EntityBrain
	{

		virtual void Init() override
		{
			std::cout << "ENTITY INIT\n";

			SetValueForMindVar(HUNGER, 12.f);
			SetValueForMindVar(MORALE, 2.f);
			SetValueForMindVar(COOKING, 2.f);
			SetValueForMindVar(ENERGY, 8.f);
		}
		
		virtual void Update(EntityManagement::Tick tick) override
		{
			//if (tick % 100000 == 0) // this is ugly ticks are too fast for the frequency by which we want the vars to be update. we neeed a cleaner way
			//{
			//	UpdateMindVars();
			//	PrintAllMindVars();
			//}

			if (tick == 500000000)
			{
				std::cout << "WILL CHECK\n";

				if (CanDoAction("MakePasta"))
				{
					std::cout << "Can Make Pasta\n";
				}
				else
				{
					std::cout << "Can't Make Pasta\n";
				}
			}
		}

		virtual void FixedUpdate(EntityManagement::Tick fixedTick) override
		{

		}

		virtual void OnDestroy() override
		{
		}
	};
}