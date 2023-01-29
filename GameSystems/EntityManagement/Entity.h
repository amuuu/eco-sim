#pragma once

#include "EntityGlobals.h"
#include "Component.h"

#include <list>
#include <memory>
#include <variant>

namespace EntityManagement
{
	using ComponentSearchRes = std::variant<bool, std::shared_ptr<Component>>;

	class Entity
	{
		friend class EntityManager;

	public:

		virtual void OnConstruct() = 0;
		virtual void OnDestroy() { };
		
		void AddComponent(Component* component);

		void RemoveComponent(Component* component);
		void RemoveComponent(ID componentId);
		template<typename ComponentType>
		void RemoveComponent();
		
		ComponentSearchRes GetComponent(ID componentId);
		template<typename ComponentType>
		ComponentSearchRes GetComponent();
		
		std::list<Component*>* GetAllComponents();

		ID Id;

		void SetCreationTickStamp(HiResTimeStamp tick);
		HiResTimeStamp GetCreationTickStamp() const;
	
	private:
		
		void InitComponents();;
		void UpdateComponents();;
		void FixedUpdateComponents();;
		void DestroyComponents();;

	private:
		
		HiResTimeStamp creationTickStamp{};

		std::list<Component*> components{};
	};
}