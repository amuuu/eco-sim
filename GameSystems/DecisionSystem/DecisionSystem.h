#pragma once

#include "../../ExternalTools/nlohmann-json.hpp"

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include <memory>

namespace DecisionSystem
{
	using json = nlohmann::json;
	using StateOfMindId = std::string;

#define HUNGER "hunger"
#define MORALE "morale"
#define SMARTNESS "smartness"
#define FOODY "foody"
	
	
	struct StateOfMindAffector;

	enum ConditionalAffectiveness { IfAmountIsMore, IfAmountIsLess, None };

	struct StateOfMindElement
	{
		StateOfMindId name;
		std::string category;
		float min, max;
		bool isAutoUpdatedInTicks;
		float autoUpdateAmount;
		std::vector<StateOfMindAffector> affectors;

		explicit StateOfMindElement(const StateOfMindId& name,
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

		StateOfMindElement() = default;
	};

	struct StateOfMindAffector
	{
		const StateOfMindId affectorStateOfMindName;
		const float amountPerTick;
		const ConditionalAffectiveness activeIfCondition;
		const float activeIfsValue;

		StateOfMindAffector(
			const StateOfMindId& affectorStateOfMindName,
			const float& amountPerTick,
			const ConditionalAffectiveness& activeIfCondition,
			const float& activeIfsValue) :
			affectorStateOfMindName(affectorStateOfMindName),
			amountPerTick(amountPerTick),
			activeIfCondition(activeIfCondition),
			activeIfsValue(activeIfsValue)
		{}
	};

	class CentralDecisionDriver
	{
	public:

		std::map<StateOfMindId, StateOfMindElement> stateOfMindModels{};

		CentralDecisionDriver() = default;
		~CentralDecisionDriver() = default;

		void Init()
		{
			// load state of mind elements
			std::ifstream f{ "DecisionSystem/StateOfMindElements.json" };
			json data = json::parse(f);

			// iterate the array
			for (json::iterator it = data.begin(); it != data.end(); ++it)
			{
				const auto& name = (*it)["name"].get<StateOfMindId>();
				const auto& category = (*it)["category"].get<std::string>();
				const auto& min = (*it)["bounds"]["min"].get<float>();
				const auto& max = (*it)["bounds"]["max"].get<float>();
				const auto& isAutoUpdatedInTicks = (*it).contains("autoUpdateByTickAmount");
				const auto& autoUpdateAmount = (*it)["autoUpdateByTickAmount"].get<float>();

				std::vector<StateOfMindAffector> affectors{};
				for (json::iterator afit = (*it)["affectedBy"].begin(); afit != (*it)["affectedBy"].end(); ++afit)
				{
					const auto& afName = (*afit)["name"].get<StateOfMindId>();
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

					affectors.push_back(StateOfMindAffector{ afName,afAmount,afActiveConditional, afActiveIfsValue });
				}

				stateOfMindModels.emplace(name, std::move(StateOfMindElement{ name,category,min,max,isAutoUpdatedInTicks,autoUpdateAmount,affectors }));
			}

			f.close();

			// load actions db
		}

	};

	class StateOfMindContainer
	{
	public:
		void SetValueForStateOfMind(const StateOfMindId id, float value) { stateOfMindValues[id] = value; }
		void ChangeValueForStateOfMind(const StateOfMindId id, float value) { stateOfMindValues[id] += value; }
		float GetValueForStateOfMind(const StateOfMindId id) { return stateOfMindValues[id]; }

		void PrintAllStateOfMinds()
		{
			for (auto const& [key, val] : stateOfMindValues)
				std::cout << key << ':' << val << std::endl;
		}

		void SetCentralDecisionDriver(std::shared_ptr<CentralDecisionDriver> driver) { centralDecisionDriver = driver; }

		void UpdateStateOfMinds()
		{
			for (auto const& [key, val] : stateOfMindValues)
			{
				ChangeValueForStateOfMind(key, centralDecisionDriver.get()->stateOfMindModels[key].autoUpdateAmount);
			}
		}

	private:
		std::map<const StateOfMindId, float> stateOfMindValues{};
		std::shared_ptr<CentralDecisionDriver> centralDecisionDriver;
	};

}