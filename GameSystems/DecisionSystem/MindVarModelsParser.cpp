#include "MindVarModelsParser.h"
#include <GameSystems/GeneralTools/Logger.h>

using namespace DecisionSystem;

void MindVarModelsParser::Init(const std::string& mindVarsConfigsPath, ParsingMode varsParsingMode, const std::string& actionConfigsPath, ParsingMode actionsParsingMode)
{
	this->mindVarsConfigsPath = mindVarsConfigsPath;
	this->actionConfigsPath = actionConfigsPath;

	ParseConfigs();
}

void MindVarModelsParser::ParseConfigs()
{
	if (mindVarsParsingMode == ParsingMode::JSON)
		ParseMindVarElementsJSON();
	else if (mindVarsParsingMode == ParsingMode::CSV)
		ParseMindVarElementsCSV();
	else
		LOG_ERR("Invalid parsing type for mind vars");

	if (actionsParsingMode == ParsingMode::JSON)
		ParseActionsJSON();
	else if (mindVarsParsingMode == ParsingMode::CSV)
		ParseActionsCSV();
	else
		LOG_ERR("Invalid parsing type for actions");

}

void MindVarModelsParser::ParseMindVarElementsJSON()
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

void DecisionSystem::MindVarModelsParser::ParseMindVarElementsCSV()
{
	CSVParser::ParserSettings settings{};
	settings.ignoredFirstRowsCount = 2;
	settings.parseHarshly = true;

	CSVParser::Parser<std::string, float, std::string, float, float, float, std::string, float, float> 
		parser{ mindVarsConfigsPath, settings };

	parser.Parse();

	// ....
}

void MindVarModelsParser::ParseActionsJSON()
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

void DecisionSystem::MindVarModelsParser::ParseActionsCSV()
{
	CSVParser::ParserSettings settings{};
	settings.ignoredFirstRowsCount = 2;
	settings.parseHarshly = true;

	CSVParser::Parser<std::string, float, std::string, float, float, float, std::string, float, float>
		parser{ mindVarsConfigsPath, settings };

	parser.Parse();

	std::string action_name{}; float action_minscore{}; 
	std::string var_name{}; float var_coeff{}; float var_min{}; float var_max{}; 
	std::string reward_name{}; float reward_absoluteamount{}; float reward_diffamount{};
	
	const std::string empty = CSVParser::EMPTY_STRING;

	ActionModel currentActionModel{};
	std::vector<ActionFormulaVariable> currentActionFormulaVars{};
	std::vector<ActionReward> currentActionRewards{};

	for (int row = 0; row < parser.GetRowCount(); row++)
	{
		parser.GetRowData<std::string, float, std::string, float, float, float, std::string, float, float>
			(row, 
				action_name, action_minscore, 
				var_name, var_coeff, var_min, var_max,
				reward_name, reward_absoluteamount, reward_diffamount);

		if (action_name != empty)
		{
			if (actionModels.size() > 0)
			{
				if (currentActionFormulaVars.size() > 0)
				{
					currentActionModel.conditionVariables = std::move(currentActionFormulaVars);
					currentActionFormulaVars.clear();
				}
				if (currentActionRewards.size() > 0)
				{
					currentActionModel.rewards = std::move(currentActionRewards);
					currentActionRewards.clear();
				}

				actionModels.emplace(currentActionModel.name, ActionModel{ currentActionModel });
			}

			currentActionModel = ActionModel{};
			currentActionModel.name = action_name;
			currentActionModel.minScore = action_minscore;
		}

		if (var_name != empty)
		{
			enum BoundType boundType = None;
			float val{};
			
			if ((var_min != 0.f && var_max == 0.f) || (var_min == 0.f && var_max == 0.f))
			{
				boundType = Min;
				val = var_min;
			}
			else if (var_min == 0.f && var_max != 0.f)
			{
				boundType = Max;
				val = var_max;
			}

			currentActionFormulaVars.push_back(ActionFormulaVariable{ var_name, val, boundType, var_coeff });
		}

		if (reward_name != empty)
		{
			enum RewardEffect rewardType = NaN;
			float val{};

			if ((reward_absoluteamount != 0.f && reward_diffamount == 0.f) || (reward_absoluteamount == 0.f && reward_diffamount == 0.f))
			{
				rewardType = Absolute;
				val = reward_absoluteamount;
			}
			else if (reward_absoluteamount == 0.f && reward_diffamount != 0.f)
			{
				rewardType = Diff;
				val = reward_diffamount;
			}
			
			currentActionRewards.push_back(ActionReward{ reward_name, rewardType, val});
		}

	}
}
