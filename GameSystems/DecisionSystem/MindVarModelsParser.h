#pragma once

#include "DecisionSystemGlobals.h"
#include "MindVarModel.h"
#include "ActionModel.h"

#include "GameSystems/GeneralTools/Singleton.h"
#include "nlohmann-json.hpp"


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
	public:

		std::map<MindVarId, MindVarModel> models;

		GENERATE_SINGLETON_GETTER(DecisionSystem::MindVarModelsParser)

		void Init()
		{
			ParseConfigs();
		}

		void ParseConfigs()
		{
			ParseMindVarElements();
			ParseActions();
		}

		void ParseMindVarElements()
		{
			using json = nlohmann::json;

			std::ifstream f{ "DecisionSystem/Configs/MindVars.json" };
			json data = json::parse(f);

			for (json::iterator it = data.begin(); it != data.end(); ++it)
			{
				///////////////////// GENERAL ///////////////////////////

				const auto& name = (*it)["name"].get<MindVarId>();
				const auto& category = (*it)["category"].get<std::string>();
				const auto& min = (*it)["bounds"]["min"].get<float>();
				const auto& max = (*it)["bounds"]["max"].get<float>();
				const auto& isAutoUpdatedInTicks = (*it).contains("autoUpdateByTickAmount");
				const auto& autoUpdateAmount = (*it)["autoUpdateByTickAmount"].get<float>();

				
				///////////////////// AFFECTORS ///////////////////////////

				std::vector<MindVarAffector> affectors{};
				for (json::iterator afit = (*it)["affectedBy"].begin(); afit != (*it)["affectedBy"].end(); ++afit)
				{
					const auto& afName = (*afit)["name"].get<MindVarId>();
					const auto& afAmount = (*afit)["amountPerTick"].get<float>();

					enum ConditionalAffectiveness afActiveConditional = Never;
					float afActiveIfsValue = 0.0f;

					if ((*afit).contains("ifTotalIsLessThan")) 
					{
						afActiveConditional = IfAmountIsLess;
						afActiveIfsValue = (*afit)["ifTotalIsLessThan"].get<float>();
					}
					
					if((*afit).contains("ifTotalIsMoreThan"))
					{
						afActiveConditional = IfAmountIsMore;
						afActiveIfsValue = (*afit)["ifTotalIsMoreThan"].get<float>();
					}

					affectors.push_back(MindVarAffector{ afName,afAmount,afActiveConditional, afActiveIfsValue });
				}

				models.emplace(name, MindVarModel{ name,category,min,max,isAutoUpdatedInTicks,autoUpdateAmount,affectors });
			}

			f.close();
		}
	
		void ParseActions()
		{
			using json = nlohmann::json;

			std::ifstream f{ "DecisionSystem/Configs/Actions.json" };
			json data = json::parse(f);

			for (json::iterator it = data.begin(); it != data.end(); ++it)
			{
				///////////////////// GENERAL ///////////////////////////

				const auto& name = (*it)["name"].get<ActionId>();

				///////////////////// VARIABLES ///////////////////////////

				std::vector<ActionFormulaVariable> fVariables{};
				for (json::iterator fvIt = (*it)["formulaVariables"].begin(); fvIt != (*it)["formulaVariables"].end(); ++fvIt)
				{
					const auto& fvName = (*fvIt)["name"].get<MindVarId>();

					enum BoundType fvBoundType = None;
					float fvBound = 0.0f;
					if ((*fvIt).contains("min"))
					{
						fvBoundType = Min;
						fvBound = (*fvIt)["min"].get<float>();
					}
					else if ((*fvIt).contains("max"))
					{
						fvBoundType = Max;
						fvBound = (*fvIt)["max"].get<float>();
					}

					float fvCoefficient = 0.0f;
					if ((*fvIt).contains("coeff"))
					{
						fvCoefficient = (*fvIt)["coeff"].get<float>();
					}

					fVariables.push_back(ActionFormulaVariable{ fvName, fvBound, fvBoundType, fvCoefficient });
				}

				///////////////////// FORMULA ///////////////////////////

				std::string formula{};
				if ((*it).contains("formula"))
				{

				}
				else
				{

				}

				///////////////////// REWARDS ///////////////////////////

				std::vector<ActionReward> rewards{};
				for (json::iterator rIt = (*it)["rewards"].begin(); rIt != (*it)["rewards"].end(); ++rIt)
				{
					const auto& rName = (*rIt)["name"].get<MindVarId>();

					enum RewardEffect rEffectType = NaN;
					float rAmount = 0.0f;
					if ((*rIt).contains("absoluteAmount"))
					{
						rEffectType = Absolute;
						rAmount = (*rIt)["absoluteAmount"];
					}
					else if ((*rIt).contains("changeAmount"))
					{
						rEffectType = Diff;
						rAmount = (*rIt)["changeAmount"];
					}

					rewards.push_back(ActionReward{ rName, rEffectType, rAmount });
				}
			}

			f.close();
		}
	
	};

}