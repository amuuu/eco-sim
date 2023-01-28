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

		// todo: remove component by id and type
		
		ComponentSearchRes GetComponentById(ID componentId);

		// todo: get component by template type
		
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