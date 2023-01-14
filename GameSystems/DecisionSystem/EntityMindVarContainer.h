#pragma once

#include "DecisionSystemGlobals.h"
#include "MindVarModelsParser.h"

#include <map>
#include <memory>
#include <iostream>
#include "MindVarModelsParser.h"

namespace DecisionSystem
{

	class EntityMindVarContainer
	{
	public:
		
		void SetValueForMindVar(const MindVarId id, float value) { mindVarValues[id] = value; }
		void ChangeValueForMindVar(const MindVarId id, float value) { mindVarValues[id] += value; }
		float GetValueForMindVar(const MindVarId id) { return mindVarValues[id]; }

		void PrintAllMindVars()
		{
			for (auto const& [key, val] : mindVarValues)
				std::cout << key << ':' << val << std::endl;
		}

		void UpdateMindVars()
		{
			for (auto const& [targetVar, targetVarVal] : mindVarValues)
			{
				// direct changes
				ChangeValueForMindVar(targetVar, MindVarModelsParser::GetInstance()->models[targetVar].autoUpdateAmount);

				// affectors
				for (auto const& affector : MindVarModelsParser::GetInstance()->models[targetVar].affectors)
				{
					if (mindVarValues.find(affector.name) != mindVarValues.end())
					{
						if ((affector.activeIfCondition != None && (affector.activeIfCondition * (mindVarValues[affector.name] - affector.activeIfsValue) > 0.f))
							|| 
							(affector.activeIfCondition == None))
						{
							ChangeValueForMindVar(targetVar, affector.amountPerTick);
						}
					}
				}
			}
		}

	private:

		std::map<const MindVarId, float> mindVarValues{};
	
	};
}