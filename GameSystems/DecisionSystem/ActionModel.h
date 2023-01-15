#pragma once
#include "DecisionSystemGlobals.h"

namespace DecisionSystem
{
	enum BoundType { Min, Max, None };
	
	struct ActionFormulaVariable
	{
		MindVarId name;
		float bound;
		BoundType boundType;
		float coefficient;

		explicit ActionFormulaVariable(
			const MindVarId& name,
			const float& bound,
			const BoundType& boundType,
			const float& coefficient) :
			name(name),
			bound(bound),
			boundType(boundType),
			coefficient(coefficient)
		{ }
	};

	enum RewardEffect { Absolute, Diff, NaN };

	struct ActionReward
	{
		MindVarId name;
		RewardEffect effectType;
		float amount;
		
		explicit ActionReward(
			const MindVarId& name,
			const RewardEffect& effectType,
			const float& amount):
			name(name),
			effectType(effectType),
			amount(amount)
		{ }
	};

	class ActionModel
	{

	};
}