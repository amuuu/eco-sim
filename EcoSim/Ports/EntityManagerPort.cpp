#include "EntityManagerPort.h"

using namespace LayerPort;

void EntityManagerPort::Setup()
{
	entityManager.StartTheLoop();
}

void EntityManagerPort::Shutdown()
{
}

void EntityManagerPort::OnPrompt(const Prompt& prompt)
{
	if (prompt.name == "INSTANTIATE_ENTITY")
	{
		CreateNewEntity();
	}
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