#pragma once

#include "DecisionSystemGlobals.h"
#include "MindVarModel.h"

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
	class CentralDecisionDriver
	{
	public:

		std::map<MindVarId, MindVarModel> MindVarModels{};

		void Init()
		{
			using json = nlohmann::json;

			// load state of mind elements
			std::ifstream f{ "DecisionSystem/Configs/MindVarElements.json" };
			json data = json::parse(f);

			// iterate the array
			for (json::iterator it = data.begin(); it != data.end(); ++it)
			{
				const auto& name = (*it)["name"].get<MindVarId>();
				const auto& category = (*it)["category"].get<std::string>();
				const auto& min = (*it)["bounds"]["min"].get<float>();
				const auto& max = (*it)["bounds"]["max"].get<float>();
				const auto& isAutoUpdatedInTicks = (*it).contains("autoUpdateByTickAmount");
				const auto& autoUpdateAmount = (*it)["autoUpdateByTickAmount"].get<float>();

				std::vector<MindVarAffector> affectors{};
				for (json::iterator afit = (*it)["affectedBy"].begin(); afit != (*it)["affectedBy"].end(); ++afit)
				{
					const auto& afName = (*afit)["name"].get<MindVarId>();
					const auto& afAmount = (*afit)["amountPerTick"].get<float>();

					enum ConditionalAffectiveness afActiveConditional = None;
					float afActiveIfsValue = 0.0f;

					if ((*afit).contains("ifTotalIsLessThan")) 
					{
						afActiveConditional = IfAmountIsLess;
						afActiveIfsValue = (*afit)["amountPerTick"].get<float>();
					}
					
					if((*afit).contains("ifTotalIsMoreThan"))
					{
						afActiveConditional = IfAmountIsMore;
						afActiveIfsValue = (*afit)["amountPerTick"].get<float>();
					}

					affectors.push_back(MindVarAffector{ afName,afAmount,afActiveConditional, afActiveIfsValue });
				}

				MindVarModels.emplace(name, MindVarModel{ name,category,min,max,isAutoUpdatedInTicks,autoUpdateAmount,affectors });
			}

			f.close();

			
			// load actions db
		
		
		
		
		}
	};
}