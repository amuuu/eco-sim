#pragma once

#include "DecisionSystemGlobals.h"
#include "MindVarModelsParser.h"

#include <map>
#include <memory>
#include <iostream>
#include "MindVarModelsParser.h"

namespace DecisionSystem
{

	class MindVarContainer
	{
	public:

		MindVarContainer()
		{

		}

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
			for (auto const& [key, val] : mindVarValues)
			{
				ChangeValueForMindVar(key, MindVarModelsParser::GetInstance()->models[key].autoUpdateAmount);
			}
		}

	private:

		std::map<const MindVarId, float> mindVarValues{};
	
	};
}