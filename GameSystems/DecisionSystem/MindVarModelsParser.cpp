#include "MindVarModelsParser.h"
#include <GameSystems/GeneralTools/Logger.h>

using namespace DecisionSystem;

void MindVarModelsParser::Init(const std::string& mindVarsConfigsPath, ParsingMode varsParsingMode, const std::string& actionConfigsPath, ParsingMode actionsParsingMode)
{
	this->mindVarsConfigsPath = mindVarsConfigsPath;
	this->mindVarsParsingMode = varsParsingMode;
	this->actionConfigsPath = actionConfigsPath;
	this->actionsParsingMode = actionsParsingMode;

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
	else if (actionsParsingMode == ParsingMode::CSV)
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

		mindVarModels.emplace(name, MindVarModel{ name,category,min,max,isAutoUpdatedInTicks,autoUpdateAmount,affectors });
	}

	f.close();
}

void MindVarModelsParser::ParseMindVarElementsCSV()
{
	CSVParser::ParserSettings settings{};
	settings.ignoredFirstRowsCount = 2;
	settings.parseHarshly = true;

	CSVParser::Parser<std::string, std::string, float, float, float, std::string, float, float, float> 
		parser{ mindVarsConfigsPath, settings };

	parser.Parse();

	std::string var_name{}; 
	std::string var_category{}; 
	float var_min{}; float var_max{}; 
	float var_autoUpdatePerTickAmount{};
	std::string affector_name{}; float affector_autoUpdatePerTickAmount{}; float affector_ifTotalLessThan{}; float affector_ifTotalMoreThan{};

	const std::string empty = CSVParser::EMPTY_STRING;

	std::vector<MindVarAffector> currentMindVarAffectors{};
	
	std::string currentName{}, currentCategory{};
	float currentMin{}, currentMax{}, currentAutoUpdateByTick{};
	bool atLeastOneVarExists{ false };

	for (int row = 0; row < parser.GetRowCount(); row++)
	{
		parser.GetRowData<
			std::string, 
			std::string, 
			float, float, 
			float, 
			std::string, float, float, float>
			(row,
				var_name, 
				var_category,
				var_min, var_max, 
				var_autoUpdatePerTickAmount,
				affector_name, affector_autoUpdatePerTickAmount, affector_ifTotalLessThan, affector_ifTotalMoreThan);

		if (var_name != empty)
		{
			if (atLeastOneVarExists)
			{
				mindVarModels.emplace(currentName, MindVarModel{ currentName, currentCategory, currentMin, currentMax, (currentAutoUpdateByTick != 0), currentAutoUpdateByTick, currentMindVarAffectors});
				currentMindVarAffectors.clear();
			}

			currentName = var_name;
			currentCategory = var_category;
			currentMin = var_min;
			currentMax = var_max;
			currentAutoUpdateByTick = var_autoUpdatePerTickAmount;
			atLeastOneVarExists = true;
		}

		if (affector_name != empty)
		{
			enum ConditionalAffectiveness conditional = Never;
			float conditionalAmount = 0.0f;

			if (affector_ifTotalLessThan != 0.f && affector_ifTotalMoreThan == 0.f)
			{
				conditional = IfAmountIsLess;
				conditionalAmount = affector_ifTotalLessThan;
			}
			else if (affector_ifTotalLessThan == 0.f && affector_ifTotalMoreThan != 0.f)
			{
				conditional = IfAmountIsMore;
				conditionalAmount = affector_ifTotalMoreThan;
			}
			else if (affector_ifTotalLessThan == 0.f && affector_ifTotalMoreThan == 0.f)
			{
				conditional = Never;
			}

			currentMindVarAffectors.push_back(MindVarAffector{ affector_name, affector_autoUpdatePerTickAmount, conditional, conditionalAmount });
		}

	}

	if (atLeastOneVarExists)
	{
		mindVarModels.emplace(currentName, MindVarModel{ currentName, currentCategory, currentMin, currentMax, (currentAutoUpdateByTick != 0), currentAutoUpdateByTick, currentMindVarAffectors });
	}

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

void MindVarModelsParser::ParseActionsCSV()
{
	CSVParser::ParserSettings settings{};
	settings.ignoredFirstRowsCount = 2;
	settings.parseHarshly = true;

	CSVParser::Parser<std::string, float, std::string, float, float, float, std::string, float, float>
		parser{ actionConfigsPath, settings };

	parser.Parse();

	std::string action_name{}; float action_minscore{}; 
	std::string var_name{}; float var_coeff{}; float var_min{}; float var_max{}; 
	std::string reward_name{}; float reward_absoluteamount{}; float reward_diffamount{};
	
	const std::string empty = CSVParser::EMPTY_STRING;

	ActionModel currentActionModel{};
	std::vector<ActionFormulaVariable> currentActionFormulaVars{};
	std::vector<ActionReward> currentActionRewards{};
	bool atLeastOneActionModelExists{ false };

	for (int row = 0; row < parser.GetRowCount(); row++)
	{
		parser.GetRowData<
			std::string, float, 
			std::string, float, float, float, 
			std::string, float, float>
			(row, 
				action_name, action_minscore, 
				var_name, var_coeff, var_min, var_max,
				reward_name, reward_absoluteamount, reward_diffamount);

		if (action_name != empty)
		{
			if (actionModels.size() > 0)
			{
				if (currentActionFormulaVars.size() > 0)
					currentActionModel.conditionVariables = std::move(currentActionFormulaVars);
				if (currentActionRewards.size() > 0)
					currentActionModel.rewards = std::move(currentActionRewards);

				actionModels.emplace(currentActionModel.name, ActionModel{ currentActionModel });

				currentActionFormulaVars.clear();
				currentActionRewards.clear();
			}

			currentActionModel = ActionModel{};
			currentActionModel.name = action_name;
			currentActionModel.minScore = action_minscore;
			atLeastOneActionModelExists = true;
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

	if (atLeastOneActionModelExists)
	{
		if (currentActionFormulaVars.size() > 0)
			currentActionModel.conditionVariables = std::move(currentActionFormulaVars);
		if (currentActionRewards.size() > 0)
			currentActionModel.rewards = std::move(currentActionRewards);

		actionModels.emplace(currentActionModel.name, ActionModel{ currentActionModel });
	}
}
