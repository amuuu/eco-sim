#pragma once

#include "DecisionSystemGlobals.h"
#include "DecisionSystem.h"

#include <map>
#include <memory>
#include <iostream>

namespace DecisionSystem
{

	class StateOfMindContainer
	{
	public:

		void SetValueForStateOfMind(const StateOfMindId id, float value) { stateOfMindValues[id] = value; }
		void ChangeValueForStateOfMind(const StateOfMindId id, float value) { stateOfMindValues[id] += value; }
		float GetValueForStateOfMind(const StateOfMindId id) { return stateOfMindValues[id]; }

		void PrintAllStateOfMinds()
		{
			for (auto const& [key, val] : stateOfMindValues)
				std::cout << key << ':' << val << std::endl;
		}

		void SetCentralDecisionDriver(std::shared_ptr<CentralDecisionDriver> driver) { centralDecisionDriver = driver; }

		void UpdateStateOfMinds()
		{
			for (auto const& [key, val] : stateOfMindValues)
			{
				ChangeValueForStateOfMind(key, centralDecisionDriver.get()->stateOfMindModels[key].autoUpdateAmount);
			}
		}

	private:
		std::map<const StateOfMindId, float> stateOfMindValues{};
		std::shared_ptr<CentralDecisionDriver> centralDecisionDriver;
	};
}