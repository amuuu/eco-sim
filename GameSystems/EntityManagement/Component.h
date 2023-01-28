#pragma once
#include "EntityGlobals.h"

namespace EntityManagement
{
	class Component
	{
	public:
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void OnDestroy() = 0;

		bool IsEnabled{ true };

		ID componentID; // todo: use this guy

		HiResTimeStamp GetCurrentTimeStamp() { return HIRES_NOW; }
	};
}