#pragma once

#include "EntityGlobals.h"
#include "Component.h"

#include <list>

namespace EntityManagement
{
	class Entity
	{
		friend class EntityManager;

	public:

		virtual void OnConstruct() = 0;
		virtual void OnDestroy() { };
		
		void AddComponent(Component* component) { components.push_back(component); }
		// todo: remove component
		// todo: get component
		// todo: get all components

		ID Id;
		void SetCreationTickStamp(HiResTimeStamp tick) { creationTickStamp = tick; }
		HiResTimeStamp GetCreationTickStamp() const { return creationTickStamp; }
	
	private:
		
		HiResTimeStamp creationTickStamp{};

		std::list<Component*> components{};

		void InitComponents() { for (const auto& c : components) { c->Init(); } };
		void UpdateComponents() { for (const auto& c : components) { c->Update(); } };
		void FixedUpdateComponents() { for (const auto& c : components) { c->FixedUpdate(); } };
		void DestroyComponents() { for (const auto& c : components) { c->OnDestroy(); } };

	};
}