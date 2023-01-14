#pragma once

#include "../EntityManagement/Entity.h"

#include "StateOfMindModelsContainer.h"

#include <memory>

namespace DecisionSystem
{
	
	class EntityWithStateOfMind : public EntityManagement::Entity, public StateOfMindContainer
	{
		// TODO: Move this to outside ///////////////
		std::shared_ptr<CentralDecisionDriver> cdd;
		//////////////////////////////////////////////

		virtual void Init() override
		{
			// TODO: Move these to outside ///////////////
			cdd = std::shared_ptr<CentralDecisionDriver>(new CentralDecisionDriver);
			cdd->Init();
			SetCentralDecisionDriver(cdd);
			//////////////////////////////////////////////


			SetValueForStateOfMind(HUNGER, 12.f);
		}
		
		virtual void Update(EntityManagement::Tick tick) override
		{
			if (tick % 100000 == 0)
			{
				UpdateStateOfMinds();
				PrintAllStateOfMinds();
			}
		}
	};
}