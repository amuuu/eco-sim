#pragma once
#include "EntityGlobals.h"

namespace EntityManagement
{
	class Component
	{
		friend class Entity;

	public:

		Component(ID id);
		~Component();

	private:

		virtual void Init();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void OnDestroy();

	public:

		HiResTimeStamp GetCurrentTimeStamp();

		bool IsEnabled{ true };
		ID id{ 0 };
	};
}