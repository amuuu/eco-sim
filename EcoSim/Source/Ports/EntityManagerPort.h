#pragma once

#include "BasePort.h"

#include <EntityManagement/EntityManager.h>
using namespace EntityManagement;

#include <string> 
#include <map>

namespace LayerPort
{

	class SimpleDumbEntity : public Entity
	{
		virtual void OnConstruct() override { }
	};


	class EntityManagerPort : public BasePort
	{
	public:

		EntityManagerPort(InterPortComHandler* interPortComHandler) : BasePort(interPortComHandler) {}
	
	private:

		virtual void Setup() override; // BasePort
		virtual void Shutdown() override; // BasePort
		virtual void UpdateDraw() override; // BasePort
		virtual void OnPrompt(const Prompt& prompt) override; // BasePort

		void CreateNewEntity();
		void CreateEntitiesBulk(int amount);
		
		void ToggleDisplayForEntity(ID& id, bool isOn);
		void ToggleDisplayForEntity(ID id);

		std::map<const ID, Entity*>* GetAllEntities();
		std::map<const ID, bool>* GetEntitiesDisplayState();
		Entity* GetEntityBasedOnID(ID id);

		void DestroyEntity(ID id);

	private:

		EntityManager entityManager{ false };
		std::map<const ID, bool> entityDisplayState{};

	private:
		int bulkInstantiateAmount{ 0 }, entityListItemIndex{ 0 };

	};
}