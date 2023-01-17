#pragma once

#include "../GameSystems/GameSystems/EventSystem/EventSystem.h"
using namespace EventSystem;

#include <iostream>
#include <typeinfo>

namespace EVENT_SYSTEM_SAMPLE
{

	struct CustomEvent : public Event
	{
		std::string content;

		CustomEvent(EventId id, const std::string& content) : content(content), Event(id) { }
		CustomEvent(EventId id) = delete;
	};

	class SimpleEventListenerClass : public EventListener
	{
	public:

		void SendEvent(EventId id, std::string content)
		{
			std::cout << objectId << " firing " << id << "\n";

			CustomEvent e{ id, content };
			EventBus::GetInstance()->PropagateEvent(e);
		}

		SimpleEventListenerClass(int id, std::vector<EventId> eventsToListenTo) : objectId(id)
		{
			EventBus::GetInstance()->RegisterEventListener(this, eventsToListenTo);
		}

		~SimpleEventListenerClass()
		{
			EventBus::GetInstance()->UnregisterEventListener(this);
		}

	private:
		
		virtual void OnEvent(Event& eventData) override
		{
			std::cout << " - " << objectId << " received " << eventData.id ;
			
			if (typeid(eventData) == typeid(CustomEvent))
			{
				auto& customPayload = dynamic_cast<CustomEvent&>(eventData);
				std::cout << " ~ custom: " << customPayload.content;
			}

			std::cout << std::endl;
		}
		
		int objectId;
	};
}