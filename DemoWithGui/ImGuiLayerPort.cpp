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

void ImGuiLayerPort::ToggleDisplayForEntity(EntityId& id, bool isOn)
{

}

void ImGuiLayerPort::ToggleDisplayForEntity(EntityId id)
{
	entityDisplayState[id] = !entityDisplayState[id];
}

std::map<const EntityId, Entity*>* ImGuiLayerPort::GetAllEntities()
{
	return entityManager.GetAllEntities();
}

std::map<const EntityId, bool>* ImGuiLayerPort::GetEntitiesDisplayState()
{
	return &entityDisplayState;
}

Entity* ImGuiLayerPort::GetEntityBasedOnID(EntityId id)
{
	return entityManager.GetEntityBasedOnID(id);
}

void ImGuiLayerPort::DestroyEntity(EntityId id)
{
	entityManager.DestroyEntity(id);
}

Tick ImGuiLayerPort::GetCurrentTick()
{ 
	return entityManager.GetCurrentTick(); 
}
