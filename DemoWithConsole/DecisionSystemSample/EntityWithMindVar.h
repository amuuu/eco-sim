#pragma once

#include "GameSystems/EntityManagement/Entity.h"
#include "GameSystems/DecisionSystem/EntityBrain.h"
using namespace DecisionSystem;

#include <memory>
#include <iostream>

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
		
		virtual void Update() override
		{
			static bool hasDone = false;
			if (!hasDone)
			{
				PrintAllVariables();

				DoActionIfPossible("MakePasta");

				PrintAllVariables();
				
				hasDone = true;
			}
		}

		virtual void FixedUpdate() override
		{
			std::cout << "FIXED\n";
		}

		virtual void OnDestroy() override
		{
		}

	};
}