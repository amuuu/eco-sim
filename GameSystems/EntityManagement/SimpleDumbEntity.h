#pragma once

#include "Entity.h"

#include <iostream>

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
			std::cout << "Simple entity update " << Id << "\n";
		}
	};
}