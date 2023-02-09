#pragma once

#include "TimerUtility.h"

#include <chrono>
#include <functional>

using namespace TimerUtility;

namespace General
{
	class Timer
	{
	public:

		inline float GetElapsed(TimeScaleType scale) { return ConvertToTimeScale(scale, GetElapsedMillis()); }

		Timer(double timescaleToRealLifeSecond, TimestampType startPoint) : timescaleToRealLifeSecond(timescaleToRealLifeSecond), startPoint(startPoint) { }
		Timer(double timescaleToRealLifeSecond) : timescaleToRealLifeSecond(timescaleToRealLifeSecond), startPoint(NOW) { }
		Timer() : timescaleToRealLifeSecond(1.), startPoint(NOW){}

		void Reset() { startPoint = NOW; }

	private:

		float GetElapsedMillis() { return (1. / timescaleToRealLifeSecond) * GetTimestampsDifferenceMillis(NOW, startPoint); }

		double timescaleToRealLifeSecond{ 1. };
		TimestampType startPoint;
	};


}