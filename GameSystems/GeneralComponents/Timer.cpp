#include "Timer.h"

using namespace GeneralComponents;


Timer::Timer() : Component(12)
{
}

void Timer::Init()
{
}

void Timer::Update()
{
	if (isActive && timerObject.ElapsedMillis() <= thisSessionCountDownTimespan)
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

	isActive = true;

	timerObject.Start();
}

void Timer::Start()
{
	timerObject.Start();
}

void Timer::Stop()
{
	isActive = false;

	timerObject.Stop();
}

float Timer::GetElapsedTimeMillis()
{
	return timerObject.ElapsedMillis();
}

void Timer::Restart()
{
	timerObject.Reset();
}
