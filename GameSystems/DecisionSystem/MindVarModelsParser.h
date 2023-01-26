#pragma once

#include "DecisionSystemGlobals.h"
#include "MindVarModel.h"
#include "ActionModel.h"

#include "GameSystems/GeneralTools/Singleton.h"
#include "ExternalTools/nlohmann-json.hpp"


#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include <memory>


namespace DecisionSystem
{	
	class MindVarModelsParser
	{
	private:
		std::string actionConfigsPath{};
		std::string mindVarsConfigsPath{};

	public:

		std::map<MindVarId, MindVarModel> models{};
		std::map<std::string, ActionModel> actionModels{};

		GENERATE_SINGLETON_GETTER(DecisionSystem::MindVarModelsParser)

		void Init(const std::string& mindVarsConfigsPath, const std::string& actionConfigsPath);

		void ParseConfigs();

		void ParseMindVarElements();
	
		void ParseActions();
	
	};

}