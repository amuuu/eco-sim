#pragma once

#include "DecisionSystemGlobals.h"
#include "MindVarModel.h"
#include "ActionModel.h"

#include "../GeneralTools/Singleton.h"
#include "../../ExternalTools/amuuu--simple-csv-parser/Source/csvparser.h"
#include "../../ExternalTools/nlohmann-json.hpp"

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <utility>
#include <memory>


namespace DecisionSystem
{	
	enum class ParsingMode { JSON, CSV, None };

	class MindVarModelsParser
	{
	private:
		
		std::string actionConfigsPath{};
		ParsingMode actionsParsingMode{ None };
		std::string mindVarsConfigsPath{};
		ParsingMode mindVarsParsingMode{ None };


		std::map<MindVarId, MindVarModel> mindVarModels{};
		std::map<std::string, ActionModel> actionModels{};

	public:

		std::map<MindVarId, MindVarModel>& GetMindVarModels() { return mindVarModels; };
		std::map<std::string, ActionModel>& GetActionModels() { return actionModels; };


		GENERATE_SINGLETON_GETTER(DecisionSystem::MindVarModelsParser);

		void Init(const std::string& mindVarsConfigsPath, ParsingMode varsParsingMode, const std::string& actionConfigsPath, ParsingMode actionsParsingMode);

		void ParseConfigs();

		void ParseMindVarElementsJSON();
		void ParseMindVarElementsCSV();

		void ParseActionsJSON();
		void ParseActionsCSV();
	
	};

}