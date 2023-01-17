#pragma once
#include "GameSystems/DecisionSystem/MindVarModelsParser.h"
#include "EntityWithMindVar.h"
using namespace DecisionSystem;
#include "../GameSystems/GameSystems/EntityManagement/EntityManager.h"
using namespace EntityManagement;


namespace DECISION_SYSTEM_SAMPLE
{

	static void EXECUTE()
	{
		MindVarModelsParser::GetInstance()->Init("DemoWithConsole/DecisionSystemSample/Configs/MindVars.json", "DemoWithConsole/DecisionSystemSample/Configs/Actions.json");

		/*EntityManager entityManager{ false };
		entityManager.EnqueueNewEntity(new EntityWithMindVar{});
		entityManager.StartTheLoop();*/
	}
}