#pragma once

#include "Entity.h"

#include <iostream>

#include <chrono> // only for printing in fixed update

namespace EntityManagement
{
	class SimpleDumbEntity : public Entity
	{
		virtual void Init() override 
		{
			std::cout << "Simple entity init " << Id << "\n";
		}
		
		virtual void Update(Tick tick) override 
		{
			//std::cout << "Simple entity update " << Id << "\n";
		}

		virtual void FixedUpdate(EntityManagement::Tick fixedTick) override
		{
			std::cout << Id << " ~ fixed: " << std::chrono::high_resolution_clock::now().time_since_epoch().count() << "\n";
		}
	};
}