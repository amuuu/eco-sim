#pragma once

#include "../GameSystems/EntityManagement/EntityManager.h"
using namespace EntityManagement;

#include <string> 
#include <map>

namespace LayerPort
{
	class SimpleDumbEntity : public Component
	{
		virtual void Init() override
		{
		}

		virtual void Update() override
		{
		}

		virtual void FixedUpdate() override
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

		void ToggleDisplayForEntity(ID& id, bool isOn);

		void ToggleDisplayForEntity(ID id);

		std::map<const ID, Entity*>* GetAllEntities();

		std::map<const ID, bool>* GetEntitiesDisplayState();

		Entity* GetEntityBasedOnID(ID id);

		void DestroyEntity(ID id);

		Tick GetCurrentTick();

	private:

		EntityManager entityManager{ false };
		std::map<const ID, bool> entityDisplayState{};
	};
}