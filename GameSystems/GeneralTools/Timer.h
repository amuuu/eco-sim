#pragma once

#include <chrono>
#include <functional>

namespace General
{
	enum class TimeScaleType
	{
		Sec, Min, Hour, Day, Week, Month, Year
	};

	class BaseTimer
	{
	public:
		
		BaseTimer(bool autoStart)
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

		void Stop()
		{
			hasStarted = false;
		}

		float Elapsed()
		{
			if (!hasStarted) return -1.f;

			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTimeStamp).count() * 0.001f * 0.001f * 0.001f;
		}

		float ElapsedMillis()
		{
			if (!hasStarted) return -1.f;

			return Elapsed() * 1000.0f;
		}

		inline float GetElapsedInScale(TimeScaleType scale)
		{
			switch (scale)
			{
			case TimeScaleType::Sec:
				return ElapsedMillis();
			case TimeScaleType::Min:
				return ElapsedMillis() / 60.;
			case TimeScaleType::Hour:
				return ElapsedMillis() / (60. * 60.);
			case TimeScaleType::Day:
				return ElapsedMillis() / (60. * 60. * 24);
			case TimeScaleType::Week:
				return ElapsedMillis() / (60. * 60. * 24 * 7);
			case TimeScaleType::Month:
				return ElapsedMillis() / (60. * 60. * 24 * 7 * 30);
			case TimeScaleType::Year:
				return ElapsedMillis() / (60. * 60. * 24 * 7 * 365);
			}
		}

	private:
		
		std::chrono::time_point<std::chrono::high_resolution_clock> startTimeStamp;
		
		bool hasStarted{ false };
	};
}