#include "EntityManagerPort.h"
#include <GeneralTools/Logger.h>

using namespace LayerPort;

void EntityManagerPort::Setup()
{
	entityManager.StartTheLoop();
}

void EntityManagerPort::Shutdown()
{
}

void LayerPort::EntityManagerPort::UpdateDraw()
{
	if (ImGui::Button("Instantiate Entity", EcoSimImGuiGlobals::LARGE_BUTT_SIZE))
	{
		CreateNewEntity();
	}

	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("Bulk Amount", &bulkInstantiateAmount, 10, 50);
	if (ImGui::Button("Bulk Instantiate Entities", EcoSimImGuiGlobals::LARGE_BUTT_SIZE))
	{
		CreateEntitiesBulk(bulkInstantiateAmount);
	}

	ImGui::NewLine();
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode("Entity List"))
	{
		for (const auto& entityData : *(GetAllEntities()))
		{
			if (ImGui::Button(std::string{ "ID: " + std::to_string(entityData.first) }.c_str()))
			{
				ToggleDisplayForEntity(entityData.first);
			}
		}

		ImGui::TreePop();
	}

	for (auto& entityDisplayData : *(GetEntitiesDisplayState()))
	{
		if (entityDisplayData.second == true)
		{
			const auto* entityContent = GetEntityBasedOnID(entityDisplayData.first);
			auto name = std::string{ "Entity " + std::to_string(entityContent->Id) };

			ImGuiWindowFlags flags = ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoCollapse;
			ImGui::SetNextWindowSize(ImVec2(180, 80));
			ImGui::SetNextWindowPos(ImVec2(350 + 100, 50 + 80 * entityListItemIndex++));
			ImGui::Begin(name.c_str(), &entityDisplayData.second, flags);

			ImGui::Text("Creation tick: %d", entityContent->GetCreationTickStamp());

			if (ImGui::Button("Kill"))
			{
				DestroyEntity(entityContent->Id);
				entityDisplayData.second = false;
			}

			ImGui::End();
		}
	}
	entityListItemIndex = 0;
			
}

void EntityManagerPort::OnPrompt(const Prompt& prompt)
{
	
}

void EntityManagerPort::CreateNewEntity()
{
	entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
	
}

void EntityManagerPort::CreateEntitiesBulk(int amount)
{
	for (int e = 0; e < amount; e++)
		CreateNewEntity();
}

void EntityManagerPort::ToggleDisplayForEntity(ID& id, bool isOn)
{
	entityDisplayState[id] = isOn;
}

void EntityManagerPort::ToggleDisplayForEntity(ID id)
{
	entityDisplayState[id] = !entityDisplayState[id];
}

std::map<const ID, Entity*>* EntityManagerPort::GetAllEntities()
{
	return entityManager.GetAllEntities();
}

std::map<const ID, bool>* EntityManagerPort::GetEntitiesDisplayState()
{
	return &entityDisplayState;
}

Entity* EntityManagerPort::GetEntityBasedOnID(ID id)
{
	return entityManager.GetEntityBasedOnID(id);
}

void EntityManagerPort::DestroyEntity(ID id)
{
	entityManager.DestroyEntity(id);
}