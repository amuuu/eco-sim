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
			BulkSetVariables({
				{ HUNGER, 70.f },
				{ MORALE, 2.f },
				{ COOKING, 70.f },
				{ ENERGY, 8.f }
			});
		}
		
		virtual void Update(EntityManagement::Tick tick) override
		{
			//if (tick % 1000 == 0) // this is ugly ticks are too fast for the frequency by which we want the vars to be update. we neeed a cleaner way
			//{
			//	UpdateVariables();
			//	PrintAllVariables();
			//}
			static bool canMakePasta = false;
			if (tick == 500000)
			{
				std::cout << "WILL CHECK\n";

				if (CanDoAction("MakePasta"))
				{
					std::cout << "Can Make Pasta\n";

					PrintAllVariables();

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

				PrintAllVariables();
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