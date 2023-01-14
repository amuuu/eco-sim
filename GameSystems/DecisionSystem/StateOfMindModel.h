#pragma once

#include "DecisionSystemGlobals.h"

namespace DecisionSystem
{
	enum ConditionalAffectiveness { IfAmountIsMore, IfAmountIsLess, None };

	struct StateOfMindAffector
	{
		const StateOfMindId affectorStateOfMindName;
		const float amountPerTick;
		const ConditionalAffectiveness activeIfCondition;
		const float activeIfsValue;

		StateOfMindAffector(
			const StateOfMindId& affectorStateOfMindName,
			const float& amountPerTick,
			const ConditionalAffectiveness& activeIfCondition,
			const float& activeIfsValue) :
			affectorStateOfMindName(affectorStateOfMindName),
			amountPerTick(amountPerTick),
			activeIfCondition(activeIfCondition),
			activeIfsValue(activeIfsValue)
		{}
	};

	struct StateOfMindModel
	{
		StateOfMindId name;
		std::string category;
		float min, max;
		bool isAutoUpdatedInTicks;
		float autoUpdateAmount;
		std::vector<StateOfMindAffector> affectors;

		explicit StateOfMindModel(const StateOfMindId& name,
			const std::string& category,
			const float& min,
			const float& max,
			const bool isAutoUpdatedInTicks,
			const float& autoUpdateAmount,
			std::vector<StateOfMindAffector>& affectors) :
			name(name),
			category(category),
			min(min), max(max),
			isAutoUpdatedInTicks(isAutoUpdatedInTicks),
			autoUpdateAmount(autoUpdateAmount),
			affectors(affectors)
		{ }

		StateOfMindModel() = default;
	};
}