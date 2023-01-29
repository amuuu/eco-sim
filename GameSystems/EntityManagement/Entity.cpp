#include "Entity.h"

#include <typeinfo>

using namespace EntityManagement;

void Entity::AddComponent(Component* component)
{
	for (const auto& c : components)
	{
		if (c == component)
			return;
	}

	components.push_back(component);
}

void Entity::RemoveComponent(Component* component)
{
	components.remove_if(
		[&](Component* c) { return (c == component); });
}

void Entity::RemoveComponent(const ID& componentId)
{
	components.remove_if(
		[&](Component* c) { return (c->id == componentId); });
}

Component* Entity::GetComponent(const ID& componentId) const
{
	for (const auto& c : components)
	{
		if (c->id == componentId)
			return c;
	}

	return nullptr;
}

std::list<Component*>* Entity::GetAllComponents()
{
	return &components;
}

void Entity::SetCreationTickStamp(HiResTimeStamp tick) 
{ 
	creationTickStamp = tick; 
}

HiResTimeStamp Entity::GetCreationTickStamp() const 
{ 
	return creationTickStamp; 
}

void Entity::InitComponents()
{ 
	for (const auto& c : components) 
		c->Init(); 
}

void Entity::UpdateComponents() 
{ 
	for (const auto& c : components) 
		c->Update(); 
}

void Entity::FixedUpdateComponents() 
{ 
	for (const auto& c : components) 
		c->FixedUpdate();
}

void Entity::DestroyComponents() 
{ 
	for (const auto& c : components)
		c->OnDestroy(); 
}
