#include "MindVarModelsParser.h"

using namespace DecisionSystem;

void MindVarModelsParser::Init(const std::string& mindVarsConfigsPath, const std::string& actionConfigsPath)
{
	this->mindVarsConfigsPath = mindVarsConfigsPath;
	this->actionConfigsPath = actionConfigsPath;

	ParseConfigs();
}

void MindVarModelsParser::ParseConfigs()
{
	ParseMindVarElements();
	ParseActions();
}

void MindVarModelsParser::ParseMindVarElements()
{
	using json = nlohmann::json;

	std::ifstream f{ mindVarsConfigsPath };
	json data = json::parse(f);

	for (json::iterator it = data.begin(); it != data.end(); ++it)
	{
		///////////////////// GENERAL ///////////////////////////

		const auto& name = (*it)["name"].get<MindVarId>();
		const auto& category = (*it)["category"].get<std::string>();
		const auto& min = (*it)["bounds"]["min"].get<float>();
		const auto& max = (*it)["bounds"]["max"].get<float>();
		const auto& isAutoUpdatedInTicks = (*it).contains("autoUpdateByTickAmount");
		float autoUpdateAmount = 0;
		if (isAutoUpdatedInTicks)
			autoUpdateAmount = (*it)["autoUpdateByTickAmount"].get<float>();

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

			if ((*afit).contains("ifTotalIsMoreThan"))
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

void MindVarModelsParser::ParseActions()
{
	using json = nlohmann::json;

	std::ifstream f{ actionConfigsPath };
	json data = json::parse(f);

	for (json::iterator it = data.begin(); it != data.end(); ++it)
	{

		ActionModel actionModel{};

		///////////////////// GENERAL ///////////////////////////

		const auto& name = (*it)["name"].get<ActionId>();
		actionModel.name = name;

		const auto& minScore = (*it)["minScore"].get<float>();
		actionModel.minScore = minScore;

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

			float fvCoefficient = 1.0f;
			if ((*fvIt).contains("coeff"))
			{
				fvCoefficient = (*fvIt)["coeff"].get<float>();
			}

			fVariables.push_back(ActionFormulaVariable{ fvName, fvBound, fvBoundType, fvCoefficient });
		}

		actionModel.conditionVariables = std::move(fVariables);

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

		actionModel.rewards = std::move(rewards);

		actionModels.emplace(name, ActionModel{ actionModel });
	}

	f.close();
}
