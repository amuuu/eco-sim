#pragma once

#include "../GameSystems/GameSystems/EntityManagement/Entity.h"
using namespace EntityManagement;

#include <iostream>
#include <chrono> // only for printing in fixed update

namespace ENTITY_MANAGEMENT_SAMPLE
{
	class SimpleDumbEntity : public Entity
	{
		virtual void Init() override 
		{
			SetFixedUpdateActiveState(false);

			std::cout << "Simple entity init " << Id << "\n";
		}
		
		virtual void Update() override 
		{
		}

		virtual void FixedUpdate() override
		{
			std::cout << Id << " ~ fixed: " << std::chrono::high_resolution_clock::now().time_since_epoch().count() << "\n";
		}

		virtual void OnDestroy() override
		{
		}
	};
}