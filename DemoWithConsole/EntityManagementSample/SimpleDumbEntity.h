#pragma once

#include "../GameSystems/GameSystems/EntityManagement/Entity.h"
using namespace EntityManagement;

#include <iostream>
#include <chrono> // only for printing in fixed update

namespace ENTITY_MANAGEMENT_SAMPLE
{
	class SimpleDumbEntity : public Entity
	{
		virtual void OnConstruct() override 
		{

		}
	};
}