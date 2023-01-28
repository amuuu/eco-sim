#pragma once
#include "EntityGlobals.h"

namespace EntityManagement
{
	class Component
	{
	public:

		Component(ID id) { this->id = id; }

		virtual void Init() { };
		virtual void Update() { };
		virtual void FixedUpdate() { };
		virtual void OnDestroy() { };

		bool IsEnabled{ true };

		ID id; // todo: use this guy

		HiResTimeStamp GetCurrentTimeStamp() { return HIRES_NOW; }
	};
}