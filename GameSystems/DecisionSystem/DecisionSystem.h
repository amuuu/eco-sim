#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>

#include "../../ExternalTools/nlohmann-json.hpp"
#include <iostream>

namespace DesicionSystem
{
	using json = nlohmann::json;

	struct StateOfMindAffector;
	
	enum ConditionalAffectiveness { IfAmountIsMore, IfAmountIsLess, None };

	struct StateOfMind
	{
		const std::string name;
		const std::string category;
		const float min, max;
		
		const bool isAutoUpdatedInTicks;
		const float autoUpdateAmount;
		/*const union AutoUpdate {
			bool isActive;
			float amount;
		} autoUpdate;*/

		const std::vector<StateOfMindAffector> affectors;

		StateOfMind(const std::string& name,
			const std::string& category,
			const float& min,
			const float& max,
			const bool isAutoUpdatedInTicks,
			const float& autoUpdateAmount,
			std::vector<StateOfMindAffector>& affectors) :
			name(name),
			category(category),
			min(min), max(max),
			isAutoUpdatedInTicks(isAutoUpdatedInTicks),
			autoUpdateAmount(autoUpdateAmount),
			affectors(affectors)
		{ }


	};

	struct StateOfMindAffector
	{
		const std::string affectorStateOfMindName;
		const float amountPerTick;
		const ConditionalAffectiveness activeIfCondition;
		const float activeIfsValue;

		StateOfMindAffector(
			const std::string affectorStateOfMindName,
			const float amountPerTick,
			const ConditionalAffectiveness activeIfCondition,
			const float activeIfsValue) :
			affectorStateOfMindName(affectorStateOfMindName),
			amountPerTick(amountPerTick),
			activeIfCondition(activeIfCondition),
			activeIfsValue(activeIfsValue)
		{}
	};

	class CentralDecisionDriver
	{
	public:

		void Init()
		{
			// load state of mind elements
			std::ifstream f{ "DecisionSystem/StateOfMindElements.json" };
			json data = json::parse(f);

			// iterate the array
			for (json::iterator it = data.begin(); it != data.end(); ++it)
			{
				const auto& name = (*it)["Name"];
				const auto& category = (*it)["Category"];
				const auto& min = (*it)["Bounds"]["Min"];
				const auto& max = (*it)["Bounds"]["Max"];
				const auto& isAutoUpdatedInTicks = (*it)["AutoUpdateByTick"]["IsActive"];
				const auto& autoUpdateAmount = (*it)["AutoUpdateByTick"]["Amount"];

				std::vector<StateOfMindAffector> affectors{};
				for (json::iterator afit = (*it)["AffectedBy"].begin(); afit != (*it)["AffectedBy"].end(); ++afit)
				{
					const auto& afName = (*afit)["Name"];
					const auto& afAmount = (*afit)["AmountPerTick"];

					enum ConditionalAffectiveness afActiveConditional = None;
					float afActiveIfsValue = 0.0f;

					if ((*afit).contains("IfTotalIsLessThan")) 
					{
						afActiveConditional = IfAmountIsLess;
						afActiveIfsValue = (*afit)["AmountPerTick"];
					}
					
					if((*afit).contains("IfTotalIsMoreThan"))
					{
						afActiveConditional = IfAmountIsMore;
						afActiveIfsValue = (*afit)["AmountPerTick"];
					}

					affectors.push_back(StateOfMindAffector{ afName,afAmount,afActiveConditional, afActiveIfsValue });
				}

				StateOfMind som{ name,category,min,max,isAutoUpdatedInTicks,autoUpdateAmount,affectors };
				std::cout << "doode";
			}

			// load actions db
		}
	};
}