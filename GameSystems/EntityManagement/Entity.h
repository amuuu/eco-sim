#pragma once

#include "EntityGlobals.h"
#include "Component.h"

#include <list>
#include <memory>
#include <variant>

namespace EntityManagement
{
	//using ComponentSearchRes = std::variant<bool, Component*>;

	class Entity
	{
		friend class EntityManager;

	public:
		
		virtual void OnConstruct() = 0;
		virtual void OnDestroy() { };
		
		void AddComponent(Component* component);

		template<typename ComponentType>
		void RemoveComponent();
		void RemoveComponent(const ID& componentId);
		void RemoveComponent(Component* component);

		template<typename ComponentType>
		ComponentType* GetComponent() const;
		Component* GetComponent(const ID& componentId) const;
		
		std::list<Component*>* GetAllComponents();

		ID Id{};

		void SetCreationTickStamp(HiResTimeStamp tick);
		HiResTimeStamp GetCreationTickStamp() const;
	
	private:
		
		void InitComponents();
		void UpdateComponents();
		void FixedUpdateComponents();
		void DestroyComponents();

	private:
		
		HiResTimeStamp creationTickStamp{};

		std::list<Component*> components{};
	};

	template<typename ComponentType>
	void Entity::RemoveComponent()
	{
		components.remove_if(
			[&](Component* c) { return (typeid(*c) == typeid(ComponentType)); });
	}

	template<typename ComponentType>
	ComponentType* Entity::GetComponent() const
	{
		for (const auto& c : components)
		{
			if (typeid(ComponentType) == typeid(*c))
				return dynamic_cast<ComponentType*>(c);
		}

		return nullptr;
	}

}