#pragma once

#include "EntityWithMind.h"

#include "GameSystems/DecisionSystem/MindVarModelsParser.h"
using namespace DecisionSystem;
#include "GameSystems/EntityManagement/EntityManager.h"
using namespace EntityManagement;

#include <GameSystems/GeneralTools/PathHelper.h>

namespace DECISION_SYSTEM_SAMPLE
{

	static void EXECUTE()
	{
		const auto mindVarsPath = GET_ABSOLUTE_PATH_STRING("\\DecisionSystemSample\\Configs\\MindVars.json");
		const auto actionsPath = GET_ABSOLUTE_PATH_STRING("\\DecisionSystemSample\\Configs\\Actions.json");

		MindVarModelsParser::GetInstance()->Init(mindVarsPath, actionsPath);


		EntityManager entityManager{ false };

		entityManager.EnqueueNewEntity(new EntityWithMind{});
		
		entityManager.StartTheLoop();
	}
}	