#pragma once

#include "DecisionSystemGlobals.h"
#include "DecisionSystem.h"

#include <map>
#include <memory>
#include <iostream>

namespace DecisionSystem
{

	class MindVarContainer
	{
	public:

		void SetValueForMindVar(const MindVarId id, float value) { MindVarValues[id] = value; }
		void ChangeValueForMindVar(const MindVarId id, float value) { MindVarValues[id] += value; }
		float GetValueForMindVar(const MindVarId id) { return MindVarValues[id]; }

		void PrintAllMindVars()
		{
			for (auto const& [key, val] : MindVarValues)
				std::cout << key << ':' << val << std::endl;
		}

		void SetCentralDecisionDriver(std::shared_ptr<CentralDecisionDriver> driver) { centralDecisionDriver = driver; }

		void UpdateMindVars()
		{
			for (auto const& [key, val] : MindVarValues)
			{
				ChangeValueForMindVar(key, centralDecisionDriver.get()->MindVarModels[key].autoUpdateAmount);
			}
		}

	private:
		std::map<const MindVarId, float> MindVarValues{};
		std::shared_ptr<CentralDecisionDriver> centralDecisionDriver;
	};
}