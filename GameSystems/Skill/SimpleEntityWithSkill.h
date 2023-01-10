#pragma once

#include "SkillHolder.h"

#include "../EntityManagement/Entity.h"

#include <iostream>

using namespace EntityManagement;

namespace Skills
{
	class SimpleEntityWithSkill : public Entity, public SkillHolder
	{
		virtual void Init() override
		{
			std::cout << "Simple entity init " << Id << "\n";

			skills.AddNewResource(new Resource{ "Crafting", 0, 100, 0 });

			skills.PrintAllResources();
		}

		virtual void Update(Tick tick) override
		{
			std::cout << "Simple entity update " << Id << "\n";
		}
	};
}