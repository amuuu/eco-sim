#pragma once

#include "GameSystems/EntityManagement/Component.h"
#include "GameSystems/GeneralTools/Timer.h"

#include <functional>

namespace GeneralComponents
{
	enum class TimerMode
	{
		InActive, Countdown, Normal
	};

	class Timer : public EntityManagement::Component
	{
	public:

		Timer();

		void Start(float countDownMillis, std::function<void()> onCountDownDoneCallback);
		
		void Start();

		void Stop();

		float GetElapsedTimeMillis();

		void Restart();

	private:
		
		virtual void Init() override;

		virtual void Update() override;

		virtual void FixedUpdate() override;

		virtual void OnDestroy() override;

	private:

		General::SimpleTimer timerObject{ false };
		
		TimerMode mode;

		float thisSessionCountDownTimespan{ 0.f };
		std::function<void()> thisSessionOnCountDownDoneCallback{};

	};
}