#pragma once

#include "DecisionSystemGlobals.h"
#include "MindVarModelsParser.h"
#include "../EntityManagement/Component.h"

#include <map>
#include <memory>
#include <list>
#include <mutex>
#include <utility>

namespace DecisionSystem
{

	class Mind : public EntityManagement::Component
	{
	public:

		Mind();

	private:

		virtual void Init() override;

		virtual void Update() override;

		virtual void FixedUpdate() override;

		virtual void OnDestroy() override;
		
		void SetValueForVariable(const MindVarId id, float value); // TODO: check min max
		
		void BulkSetVariables(std::initializer_list<std::pair< const MindVarId, float>> vars);

		void ChangeValueForVariable(const MindVarId id, float value); // TODO: check min max
		
		float GetValueForVariable(const MindVarId id);

		void PrintAllVariables();

		void UpdateVariables();

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