#pragma once

#include "DecisionSystemGlobals.h"

namespace DecisionSystem
{
	enum ConditionalAffectiveness { IfAmountIsMore, IfAmountIsLess, None };

	struct MindVarAffector
	{
		const MindVarId affectorMindVarName;
		const float amountPerTick;
		const ConditionalAffectiveness activeIfCondition;
		const float activeIfsValue;

		MindVarAffector(
			const MindVarId& affectorMindVarName,
			const float& amountPerTick,
			const ConditionalAffectiveness& activeIfCondition,
			const float& activeIfsValue) :
			affectorMindVarName(affectorMindVarName),
			amountPerTick(amountPerTick),
			activeIfCondition(activeIfCondition),
			activeIfsValue(activeIfsValue)
		{}
	};

	struct MindVarModel
	{
		MindVarId name;
		std::string category;
		float min, max;
		bool isAutoUpdatedInTicks;
		float autoUpdateAmount;
		std::vector<MindVarAffector> affectors;

		explicit MindVarModel(const MindVarId& name,
			const std::string& category,
			const float& min,
			const float& max,
			const bool isAutoUpdatedInTicks,
			const float& autoUpdateAmount,
			std::vector<MindVarAffector>& affectors) :
			name(name),
			category(category),
			min(min), max(max),
			isAutoUpdatedInTicks(isAutoUpdatedInTicks),
			autoUpdateAmount(autoUpdateAmount),
			affectors(affectors)
		{ }

		MindVarModel() = default;
	};
}