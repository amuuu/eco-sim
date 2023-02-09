#pragma once

#include "TimerUtility.h"

#include <chrono>
#include <functional>

using namespace TimerUtility;

namespace Timer
{
	class Timer
	{
	public:

		inline float GetElapsed(TimeScaleType scale) { return ConvertToTimeScale(scale, GetElapsedSecs()); }

		Timer(double timescaleToRealLifeSecond, TimestampType startPoint) : timescaleToRealLifeSecond(timescaleToRealLifeSecond), startPoint(startPoint) { }
		Timer(double timescaleToRealLifeSecond) : timescaleToRealLifeSecond(timescaleToRealLifeSecond), startPoint(NOW) { }
		Timer() : timescaleToRealLifeSecond(1.), startPoint(NOW){}

		void Reset() { startPoint = NOW; }

	private:

		float GetElapsedSecs() { return (1. / timescaleToRealLifeSecond) * GetTimestampsDifferenceSecs(NOW, startPoint); }

		double timescaleToRealLifeSecond{ 1. };
		TimestampType startPoint;
	};


}