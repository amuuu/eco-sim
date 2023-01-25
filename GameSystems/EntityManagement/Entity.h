#pragma once
#include "EntityGlobals.h"

namespace EntityManagement
{
	class Entity
	{
	public:
		virtual void Init() = 0;
		virtual void Update(Tick tick) = 0;
		virtual void FixedUpdate(Tick fixedTick) = 0;
		virtual void OnDestroy() = 0;

		void SetFixedUpdateActiveState(bool isActive) { isFixedUpdateActive = isActive; }
		bool IsFixedUpdateActive() const { return isFixedUpdateActive; }
		
		EntityId Id;

		void SetCreationTickStamp(Tick tick) { creationTickStamp = tick; }
		Tick GetCreationTickStamp() const { return creationTickStamp; }

	private:
		
		bool isFixedUpdateActive{ false };
		Tick creationTickStamp{ -1 };
	};
}