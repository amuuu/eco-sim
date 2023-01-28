#pragma once

#include <chrono>
#include <functional>

namespace General
{
	class SimpleTimer
	{
	public:
		
		SimpleTimer(bool autoStart)
		{
			if (autoStart)
				Start();
		}

		void Start()
		{
			Reset();
			hasStarted = true;
		}

		bool HasStarted() 
		{ 
			return hasStarted; 
		}

		void Reset()
		{
			startTimeStamp = std::chrono::high_resolution_clock::now();
		}

		float Elapsed()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTimeStamp).count() * 0.001f * 0.001f * 0.001f;
		}

		float ElapsedMillis()
		{
			return Elapsed() * 1000.0f;
		}

	private:
		
		std::chrono::time_point<std::chrono::high_resolution_clock> startTimeStamp;
		
		bool hasStarted{ false };
	};


	//class CountDownTimer : public Timer
	//{
	//public:

	//	CountDownTimer(float deadlineMillis, std::function<void()> onTimerFinished = NULL) : Timer()
	//	{

	//	}

	//};
}