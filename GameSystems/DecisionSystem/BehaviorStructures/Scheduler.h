#pragma once

#include "../../GeneralTools/Timer.h"
#include "../../GeneralTools/TimerUtility.h"
using namespace TimerUtility;

#include <functional>
#include <vector>
#include <queue>

namespace Scheduler
{
	struct Activity
	{
		virtual inline bool MustDoNow(Timer::Timer& timer) = 0;
		virtual void DoAction() = 0;

		Activity(std::function<void()> action) : action(action) {}
		Activity() = default;

	protected:

		std::function<void()> action;
	};

	struct OneOffActivity : public Activity
	{
		TimestampType targetMoment{};

		OneOffActivity(TimestampType targetMoment, std::function<void()> action)
			: targetMoment(targetMoment), Activity(action)
		{
		}

		OneOffActivity(float fromNowMillis, std::function<void()> action) : Activity(action)
		{
			targetMoment = NOW + std::chrono::milliseconds(static_cast<int>(fromNowMillis));
		}

		virtual bool MustDoNow(Timer::Timer& timer) override
		{
			if (alreadyStarted)
				return false;

			auto diff = GetTimestampsDifferenceMillis(targetMoment, NOW);
			if (diff >= 0 && diff <= 0.07f)
			{
				if (!alreadyStarted)
				{
					alreadyStarted = true;
					return true;
				}
			}

			return false;
		}

		virtual void DoAction() override
		{
			action();
		}

	private:
		bool alreadyStarted{ false };
	};

	struct PeriodicActivity : public Activity
	{
		PeriodicActivity(
			TimeScaleType timeScale,
			float offsetInTimeScale,
			float periodValue,
			float maxAllowedLength,
			std::function<void()> action)
			: timeScale(timeScale),
			offsetInTimeScale(offsetInTimeScale),
			periodValue(periodValue),
			maxAllowedLength(maxAllowedLength),
			Activity(action)
		{
		}

		virtual inline bool MustDoNow(Timer::Timer& timer) override
		{
			bool mustDo{ false };

			auto elapsed = timer.GetElapsed(timeScale);

			if (!hasStarted)
			{
				if (elapsed < offsetInTimeScale)
				{
					mustDo = false;
				}
				else if (elapsed >= offsetInTimeScale)
				{
					hasStarted = true;
					mustDo = true;
				}
			}
			else
			{
				if ((elapsed - lastTimeValue >= periodValue))
					mustDo = true;
				else
					mustDo = false;
			}

			if (mustDo)
			{
				lastTimeValue = elapsed;
				return true;
			}
			else
			{
				return false;
			}
		}

		virtual void DoAction() override
		{
			action();
		}

	private:

		TimeScaleType timeScale;
		float offsetInTimeScale{ .5f };
		float periodValue{ 1.f };
		float maxAllowedLength{ 1.f };

		float lastTimeValue{};
		bool hasStarted{ false };
	};

	class ScheduleManager
	{
	public:

		std::vector<Activity*> activities{};

		~ScheduleManager()
		{
			for (auto& a : activities)
				delete a;
		}

		void MarkToRemove(Activity* toRemove)
		{
			activitiesToRemove.push(toRemove);
		}

		void RemoveDisposableActivities()
		{
			while (!activitiesToRemove.empty())
			{
				auto* front = activitiesToRemove.front();

				using it = std::vector<Activity*>::iterator;
				it iter = activities.begin();
				bool found{ false };
				do
				{
					if (*iter == front)
					{
						found = true;
						break;
					}
					iter++;

				} while (iter != activities.end());

				if (found)
					activities.erase(iter);

				activitiesToRemove.pop();
				delete front;
			}
		}

	private:
		std::queue<Activity*> activitiesToRemove{};
	};

}