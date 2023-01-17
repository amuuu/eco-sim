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

		void SetFixedUpdateActiveState(bool isActive) { isFixedUpdateActive = isActive; }
		bool IsFixedUpdateActive() { return isFixedUpdateActive; }
		
		EntityId Id;
	
	private:
		bool isFixedUpdateActive{ false };
	};
}