#pragma once
#include "GameSystems/DecisionSystem/BehaviorStructures/Scheduler.h"
using namespace Scheduler;

#include <iostream>
#include <thread>

namespace SCHEDULER_SAMPLE
{
	static void EXECUTE()
	{
		Timer::Timer timer{};

		ScheduleManager sm{};

		PeriodicActivity* sayHello =
			new PeriodicActivity{
				TimeScaleType::Sec,
				0.2f, 2.f, 2.f,
				[]() {  std::cout << "hello!" << std::endl;  }
		};

		PeriodicActivity* shit =
			new PeriodicActivity{
				TimeScaleType::Sec,
				0.5f, 4.f, 2.f,
				[]() { std::cout << "shit" << std::endl; }
		};

		OneOffActivity* shout =
			new OneOffActivity{
				750.f,
				[]() { std::cout << "~~~~~~~~~ one off!" << std::endl; }
		};

		sm.activities.push_back(sayHello);
		sm.activities.push_back(shit);
		sm.activities.push_back(shout);

		using namespace std::chrono_literals;
		while (true)
		{
			std::this_thread::sleep_for(20ms);

			for (auto& activity : sm.activities)
			{
				if (activity->MustDoNow(timer))
				{
					std::cout << "(" << timer.GetElapsed(TimeScaleType::Sec) << ")" << std::endl;

					activity->DoAction();

					if (typeid(activity) == typeid(OneOffActivity))
						sm.MarkToRemove(activity);
				}
			}

			sm.RemoveDisposableActivities();
		}
	}
}