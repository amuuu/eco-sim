#pragma once

#include "GameSystems/EntityManagement/Entity.h"
#include "GameSystems/DecisionSystem/EntityBrain.h"
using namespace DecisionSystem;

#include <memory>

namespace DECISION_SYSTEM_SAMPLE
{
	
	class EntityWithMindVar : public EntityManagement::Entity, public DecisionSystem::EntityBrain
	{

		virtual void Init() override
		{
			SetValueForMindVar(HUNGER, 70.f);
			SetValueForMindVar(MORALE, 2.f);
			SetValueForMindVar(COOKING, 70.f);
			SetValueForMindVar(ENERGY, 8.f);
		}
		
		virtual void Update(EntityManagement::Tick tick) override
		{
			//if (tick % 1000 == 0) // this is ugly ticks are too fast for the frequency by which we want the vars to be update. we neeed a cleaner way
			//{
			//	UpdateMindVars();
			//	PrintAllMindVars();
			//}
			static bool canMakePasta = false;
			if (tick == 500000)
			{
				std::cout << "WILL CHECK\n";

				if (CanDoAction("MakePasta"))
				{
					std::cout << "Can Make Pasta\n";

					PrintAllMindVars();

					canMakePasta = true;
				}
				else
				{
					std::cout << "Can't Make Pasta\n";

					canMakePasta = false;
				}
			}

			if (canMakePasta && tick == 1500000)
			{
				std::cout << "Making pasta if it's allowed...\n";
				
				StartDoingAction("MakePasta");

				PrintAllMindVars();
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