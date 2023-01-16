#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <array>
#include <list>


namespace EventSystem
{
	using EventId = unsigned short;

	struct EventPayload { 
		/*virtual EventPayload() = 0;*/
	};

	class EventListener
	{
	public:
		virtual void OnEvent(EventId id, EventPayload payload) = 0
	};

	class EventSystem
	{
	public:
		
		// Single event
		void RegisterEventListener(EventListener* listener, EventId targetEventId)
		{
			eventBus[targetEventId].push_back(listener);
		}

		// Multiple events
		void RegisterEventListener(EventListener* listener, std::vector<EventId> targetEventIds)
		{
			for (const auto& id : targetEventIds)
				eventBus[id].push_back(listener);
		}

		// Wildcard; All events
		void RegisterEventListener(EventListener* listener) 
		{
			auto it = eventBus.begin();
			while (it != eventBus.end())
			{
				(*it).second.push_back(listener);
				++it;
			}
		}


		void UnregisterEventListener()
		{
			auto it = eventBus.begin();
			while (it != eventBus.end())
			{
				//

				++it;
			}
		}

		void PropagateEvent(EventId id, EventPayload payload)
		{
			for (auto* listener : eventBus[id])
				listener->OnEvent(id, payload);
		}

		EventSystem() = default;

	private:

		std::map<EventId, std::vector<EventListener*>> eventBus{};

	};
}