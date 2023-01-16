#pragma once

#include "GameSystems/GeneralTools/Singleton.h"

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <array>
#include <list>


namespace EventSystem
{
	using EventId = unsigned short;

	struct Event { 
		
		virtual ~Event() {};
		
		EventId id;
		Event(EventId id) : id(id) {}
	};

	class EventListener
	{
	public:
		virtual void OnEvent(Event& eventData) = 0;
	};

	class EventBus
	{
	public:
		
		GENERATE_SINGLETON_GETTER(EventSystem::EventBus)

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


		void UnregisterEventListener(EventListener* listener)
		{
			auto eventIt = eventBus.begin();
			while (eventIt != eventBus.end())
			{
				using Iterator = std::vector<EventListener*>::iterator;

				//Iterator targetIt = (*eventIt).second.end()+1;
				Iterator targetIt{};

				bool listenerExistsForThisEvent{ false };

				for (Iterator eventListenersIt = (*eventIt).second.begin(); eventListenersIt != (*eventIt).second.end(); ++eventListenersIt)
				{
					if ((*eventListenersIt) == listener)
					{
						targetIt = eventListenersIt;
						listenerExistsForThisEvent = true;
						break;
					}
				}

				if (listenerExistsForThisEvent)
				//if (*targetIt != nullptr)
				//if (targetIt != (*eventIt).second.end()+1)
					(*eventIt).second.erase(targetIt);

				++eventIt;
			}
		}

		void PropagateEvent(Event& eventData)
		{
			for (auto* listener : eventBus[eventData.id])
				listener->OnEvent(eventData);
		}

		void Init()
		{
			// Proly sth?
		}

		EventBus() = default;

	private:

		std::map<EventId, std::vector<EventListener*>> eventBus{};

	};
}