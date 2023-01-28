#pragma once
#include "EntityGlobals.h"

namespace EntityManagement
{
	class Entity
	{
	public:
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void OnDestroy() = 0;

		EntityId Id;

		void SetCreationTickStamp(HiResTimeStamp tick) { creationTickStamp = tick; }
		HiResTimeStamp GetCreationTickStamp() const { return creationTickStamp; }
		HiResTimeStamp GetCurrentTimeStamp() { return HIRES_NOW; }
	
	private:
		
		HiResTimeStamp creationTickStamp{};
	};
}