#pragma once

#include "EventSystem.h"

#include <iostream>

namespace EventSystem
{
	class SimpleEventListenerClass : public EventListener
	{
	public:

		void SendEvent(int id)
		{
			EventBus::GetInstance()->PropagateEvent(id, EventPayload{});
		}

		SimpleEventListenerClass(int id, std::vector<EventId>eventsToListenTo) : objectId(id)
		{
			EventBus::GetInstance()->RegisterEventListener(this, eventsToListenTo);
		}

	private:
		
		virtual void OnEvent(EventId id, EventPayload payload) override
		{
			std::cout << objectId << " received " << id << "\n";
		}
		
		int objectId;

	};
}