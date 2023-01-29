#include "Timer.h"

#include "../GeneralTools/Logger.h"

using namespace GeneralComponents;

Timer::Timer() : Component(2)
{
	mode = TimerMode::InActive;
}

void Timer::Init()
{

}

void Timer::Update()
{
	if (mode == TimerMode::Normal)
	{
		LOG_INFO(timerObject.ElapsedMillis());
	}

	if (mode == TimerMode::Countdown && timerObject.ElapsedMillis() <= thisSessionCountDownTimespan)
	{
		thisSessionOnCountDownDoneCallback();
		Stop();
	}
}

void Timer::FixedUpdate()
{

}

void Timer::OnDestroy()
{

}

void Timer::Start(float countDownMillis, std::function<void()> onCountDownDoneCallback)
{
	thisSessionCountDownTimespan = countDownMillis;
	thisSessionOnCountDownDoneCallback = onCountDownDoneCallback;

	mode = TimerMode::Countdown;

	timerObject.Start();
}

void Timer::Start()
{
	mode = TimerMode::Normal;

	timerObject.Start();
}

void Timer::Stop()
{
	mode = TimerMode::InActive;

	timerObject.Stop();
}

float Timer::GetElapsedTimeMillis()
{
	return timerObject.ElapsedMillis();
}

void Timer::Restart()
{
	thisSessionCountDownTimespan = -1.f;
	timerObject.Reset();
}
