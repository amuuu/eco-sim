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
		const auto mindVarsPathJSON = GET_ABSOLUTE_PATH_STRING("\\DecisionSystemSample\\Configs\\MindVars.json");
		const auto mindVarsPathCSV = GET_ABSOLUTE_PATH_STRING("\\DecisionSystemSample\\Configs\\MindVars.csv");
		const auto actionsPathJSON = GET_ABSOLUTE_PATH_STRING("\\DecisionSystemSample\\Configs\\Actions.json");
		const auto actionsPathCSV = GET_ABSOLUTE_PATH_STRING("\\DecisionSystemSample\\Configs\\Actions.csv");

		MindVarModelsParser::GetInstance()->Init(mindVarsPathCSV, ParsingMode::CSV, actionsPathCSV, ParsingMode::CSV);


		EntityManager entityManager{ false };

		entityManager.EnqueueNewEntity(new EntityWithMind{});
		
		entityManager.StartTheLoop();


	}
}	