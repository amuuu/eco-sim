#include "EntityBrain.h"

using namespace DecisionSystem;

void EntityBrain::SetValueForMindVar(const MindVarId id, float value) { mindVarValues[id] = value; }

void EntityBrain::ChangeValueForMindVar(const MindVarId id, float value) { mindVarValues[id] += value; }

float EntityBrain::GetValueForMindVar(const MindVarId id) { return mindVarValues[id]; }

void EntityBrain::PrintAllMindVars()
{
	for (auto const& [key, val] : mindVarValues)
		std::cout << key << ':' << val << std::endl;
}

void EntityBrain::UpdateMindVars()
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

void EntityBrain::DoActionIfPossible(const std::string& actionName)
{
	if (CanDoAction(actionName))
	{
		StartDoingAction(actionName, true);
	}
}

bool EntityBrain::CanDoAction(const std::string& actionName)
{
	auto& actions = MindVarModelsParser::GetInstance()->actionModels;

	if (actions.find(actionName) == actions.end())
		return false;

	const auto& targetModel = actions[actionName];

	float score = 0.f;

	for (const auto& cv : targetModel.conditionVariables)
	{
		if (mindVarValues.find(cv.name) != mindVarValues.end())
		{
			const auto& val = mindVarValues[cv.name];

			if (static_cast<float>((cv.bound - val) * static_cast<int>(cv.boundType)) > 0.f)
			{
				score += cv.coefficient * val;
			}

		} // else you don't calculate score for that variable
	}

	return (score >= targetModel.minScore);
}

void EntityBrain::StartDoingAction(const std::string& actionName, bool doesntNeedChecking)
{
	if (doesntNeedChecking || !CanDoAction(actionName))
		return;

	onGoingActions.push_back(actionName);
}

void EntityBrain::OnActionDoneSuccessfully(const std::string& actionName)
{
	auto& actions = MindVarModelsParser::GetInstance()->actionModels;

	if (actions.find(actionName) == actions.end())
		return;

	onGoingActions.remove(actionName);

	const auto& targetModel = actions[actionName];

	for (const auto& r : targetModel.rewards)
	{
		if (mindVarValues.find(r.name) != mindVarValues.end())
		{
			if (r.effectType == Absolute)
				mindVarValues[r.name] = r.amount;
			else if (r.effectType == Diff)
				mindVarValues[r.name] += r.amount;
		}
	}
}
