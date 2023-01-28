#include "ImGuiLayerPort.h"
using namespace LayerPort;

void ImGuiLayerPort::Setup()
{
	entityManager.StartTheLoop();
}

void ImGuiLayerPort::Shutdown()
{
}

void ImGuiLayerPort::CreateNewEntity()
{
	entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
}

void ImGuiLayerPort::CreateEntitiesBulk(int amount)
{
	for (int e = 0; e < amount; e++)
		CreateNewEntity();
}

void ImGuiLayerPort::ToggleDisplayForEntity(ID& id, bool isOn)
{
	entityDisplayState[id] = isOn;
}

void ImGuiLayerPort::ToggleDisplayForEntity(ID id)
{
	entityDisplayState[id] = !entityDisplayState[id];
}

std::map<const ID, Entity*>* ImGuiLayerPort::GetAllEntities()
{
	return entityManager.GetAllEntities();
}

std::map<const ID, bool>* ImGuiLayerPort::GetEntitiesDisplayState()
{
	return &entityDisplayState;
}

Entity* ImGuiLayerPort::GetEntityBasedOnID(ID id)
{
	return entityManager.GetEntityBasedOnID(id);
}

void ImGuiLayerPort::DestroyEntity(ID id)
{
	entityManager.DestroyEntity(id);
}

Tick ImGuiLayerPort::GetCurrentTick()
{ 
	return entityManager.GetCurrentTick(); 
}
