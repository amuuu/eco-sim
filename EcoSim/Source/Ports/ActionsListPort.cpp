#include "ActionsListPort.h"

#include <GeneralTools/PathHelper.h>

#include <string>

using namespace LayerPort;

void ActionsListPort::Setup(sf::RenderWindow* window)
{
	this->window = window;

	LoadConfigs();
}

void ActionsListPort::Shutdown()
{
}

void ActionsListPort::UpdateDraw()
{
	ImGui::Begin("Actions List", 0, ImGuiWindowFlags_None);

	for (const auto& action : MindVarModelsParser::GetInstance()->GetActionModels())
	{
		if (ImGui::TreeNode(action.first.c_str())) // name
		{
			for (const auto& var : action.second.conditionVariables)
			{
				if (ImGui::TreeNode(var.name.c_str())) // name
				{
					ImGui::Text("Coeff: "); ImGui::SameLine();
					ImGui::Text(std::to_string( var.coefficient).c_str());
					ImGui::Text("Bound: "); ImGui::SameLine();
					ImGui::Text(std::to_string(var.bound).c_str());
					ImGui::Text("Bound type: "); ImGui::SameLine();
					ImGui::Text(std::to_string(BoundType{ var.boundType }).c_str());
					if (ImGui::Button("See Var Model"))
					{
						mindVarModelsDisplayState[var.name] = true;
					}

					ImGui::Separator();
					
					ImGui::TreePop();
				}
			}

			ImGui::TreePop();
		}
	}

	for (const auto& mindvar : mindVarModelsDisplayState)
	{
		if (mindvar.second)
		{
			RenderMindVar(mindvar.first);
		}
	}

	ImGui::End();
}

void ActionsListPort::OnPrompt(const Prompt& prompt)
{
}

void ActionsListPort::LoadConfigs()
{
	const auto mindVarsPathCSV = GET_ABSOLUTE_PATH_STRING("\\Configs\\MindVars.csv");
	const auto actionsPathCSV = GET_ABSOLUTE_PATH_STRING("\\Configs\\Actions.csv");

	MindVarModelsParser::GetInstance()->Init(mindVarsPathCSV, ParsingMode::CSV, actionsPathCSV, ParsingMode::CSV);

}

void LayerPort::ActionsListPort::RenderMindVar(const MindVarId& id)
{
	ImGui::Begin(id.c_str(), &mindVarModelsDisplayState[id], ImGuiWindowFlags_None);

	if (MindVarModelsParser::GetInstance()->MindVarModelExists(id))
	{
		const auto& model = MindVarModelsParser::GetInstance()->GetMindVarModels()[id];
		
		ImGui::Text("Category: "); ImGui::SameLine();
		ImGui::Text(model.category.c_str());

		ImGui::Text("Min: "); ImGui::SameLine();
		ImGui::Text(std::to_string(model.min).c_str()); ImGui::SameLine();
		ImGui::Text("~ Max: "); ImGui::SameLine();
		ImGui::Text(std::to_string(model.max).c_str());

		ImGui::Text("Auto update ticks amount: "); ImGui::SameLine();
		if (!model.isAutoUpdatedInTicks)
			ImGui::Text("-");
		else
			ImGui::Text(std::to_string(model.autoUpdateAmount).c_str());

		ImGui::Text("Affectors: ");

		if (model.affectors.size() == 0)
		{
			ImGui::SameLine();
			ImGui::Text("-");
		}

		for (const auto& affector : model.affectors)
		{
			if (ImGui::TreeNode(affector.name.c_str())) // name
			{
				ImGui::Text("Amount per tick amount: "); ImGui::SameLine();
				ImGui::Text(std::to_string(affector.amountPerTick).c_str());

				ImGui::Text("Conditional affectiveness: "); ImGui::SameLine();
				if (affector.activeIfCondition == Never)
					ImGui::Text("Never");
				else if (affector.activeIfCondition == IfAmountIsLess)
					ImGui::Text("IfAmountIsLess");
				else if (affector.activeIfCondition == IfAmountIsMore)
					ImGui::Text("IfAmountIsMore");

				ImGui::Text("Conditional affectiveness amount: "); ImGui::SameLine();
				if (affector.activeIfCondition != Never)
					ImGui::Text(std::to_string(affector.amountPerTick).c_str());
				else
					ImGui::Text("-");

				if (ImGui::Button("See Var Model"))
				{
					mindVarModelsDisplayState[affector.name] = true;
				}

				ImGui::TreePop();
			}
		}
	}
	else
	{
		ImGui::Text("ERROR: This mind var model doesn't exist\nbut it's probably used in an action.");
	}

	ImGui::End();

}
