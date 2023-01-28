#pragma once

#include "../GameSystems/GameSystems/EntityManagement/Entity.h"
using namespace EntityManagement;

#include <iostream>
#include <chrono> // only for printing in fixed update

namespace ENTITY_MANAGEMENT_SAMPLE
{
	class SimpleDumbEntity : public Component
	{
		virtual void Init() override 
		{
		}
		
		virtual void Update() override 
		{
		}

		virtual void FixedUpdate() override
		{
		}

		virtual void OnDestroy() override
		{
		}
	};
}