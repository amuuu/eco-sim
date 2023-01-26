#pragma once
#include "GameSystems/DecisionSystem/MindVarModelsParser.h"
#include "EntityWithMindVar.h"
using namespace DecisionSystem;
#include "../GameSystems/GameSystems/EntityManagement/EntityManager.h"
using namespace EntityManagement;

#include <filesystem>
#include <algorithm>

namespace DECISION_SYSTEM_SAMPLE
{

	static void EXECUTE()
	{

		auto mindVarsPath = std::string{ std::filesystem::current_path().string() + "\\DecisionSystemSample\\Configs\\MindVars.json" };
		auto actionsPath = std::string{ std::filesystem::current_path().string() + "\\DecisionSystemSample\\Configs\\Actions.json"};

		MindVarModelsParser::GetInstance()->Init(mindVarsPath, actionsPath);

		EntityManager entityManager{ false };
		entityManager.EnqueueNewEntity(new EntityWithMindVar{});
		entityManager.StartTheLoop();
	}
}