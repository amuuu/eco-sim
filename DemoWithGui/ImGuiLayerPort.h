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
		
		void Setup()
		{
			entityManager.StartTheLoop();
		}

		void Shutdown()
		{
		}

		void CreateNewEntity()
		{
			entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
		}

		void ToggleDisplayForEntity(EntityId& id, bool isOn)
		{

		}

		void ToggleDisplayForEntity(EntityId id)
		{
			entityDisplayState[id] = !entityDisplayState[id];
		}

		std::map<const EntityId, Entity*>* GetAllEntities()
		{
			return entityManager.GetAllEntities();
		}

		std::map<const EntityId, bool>* GetEntitiesDisplayState()
		{
			return &entityDisplayState;
		}

		Entity* GetEntityBasedOnID(EntityId id)
		{
			return entityManager.GetEntityBasedOnID(id);
		}

		void DestroyEntity(EntityId id)
		{
			entityManager.DestroyEntity(id);
		}

		Tick GetCurrentTick() { return entityManager.GetCurrentTick(); }

		void CreateEntitiesBulk(int amount)
		{
			for (int e = 0; e < amount; e++)
				CreateNewEntity();
		}

	private:

		EntityManager entityManager{ false };
		std::map<const EntityId, bool> entityDisplayState{};
	};
}