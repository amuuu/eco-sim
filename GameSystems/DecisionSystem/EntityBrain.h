#pragma once

#include "DecisionSystemGlobals.h"
#include "MindVarModelsParser.h"

#include <map>
#include <memory>
#include <iostream>
#include <list>
#include <mutex>

namespace DecisionSystem
{

	class EntityBrain
	{
	public:
		
		void SetValueForMindVar(const MindVarId id, float value); // TODO: check min max
		
		void ChangeValueForMindVar(const MindVarId id, float value); // TODO: check min max
		
		float GetValueForMindVar(const MindVarId id);

		void PrintAllMindVars();

		void UpdateMindVars();

		void DoActionIfPossible(const std::string& actionName);

		bool CanDoAction(const std::string& actionName);

		void StartDoingAction(const std::string& actionName, bool doesntNeedChecking = false);

		void OnActionDoneSuccessfully(const std::string& actionName);

	private:

		std::map<const MindVarId, float> mindVarValues{};
		std::list<std::string> onGoingActions{};
		std::mutex valueUpdateMutex{};
	
	};
}