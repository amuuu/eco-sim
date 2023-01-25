#pragma once

#include "../GameSystems/EntityManagement/EntityManager.h"
using namespace EntityManagement;

#include <string> 
#include <map>

namespace LayerPort
{
	class SimpleDumbEntity : public Entity
	{
		virtual void Init() override
		{
			SetFixedUpdateActiveState(false);
		}

		virtual void Update(Tick tick) override
		{
		}

		virtual void FixedUpdate(EntityManagement::Tick fixedTick) override
		{
		}

		virtual void OnDestroy() override
		{
		}
	};

	class ImGuiLayerPort
	{
	public:
		
		void Setup();

		void Shutdown();

		void CreateNewEntity();

		void CreateEntitiesBulk(int amount);

		void ToggleDisplayForEntity(EntityId& id, bool isOn);

		void ToggleDisplayForEntity(EntityId id);

		std::map<const EntityId, Entity*>* GetAllEntities();

		std::map<const EntityId, bool>* GetEntitiesDisplayState();

		Entity* GetEntityBasedOnID(EntityId id);

		void DestroyEntity(EntityId id);

		Tick GetCurrentTick();

	private:

		EntityManager entityManager{ false };
		std::map<const EntityId, bool> entityDisplayState{};
	};
}