#pragma once
#include "EntityGlobals.h"

namespace EntityManagement
{
	class Component
	{
		friend class Entity;

	public:

		Component(ID id);

		virtual void Init();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void OnDestroy();

		HiResTimeStamp GetCurrentTimeStamp();

		bool IsEnabled{ true };
		ID id{ 0 };
	};
}