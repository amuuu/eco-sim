#pragma once

#include <chrono>

namespace TimerUtility
{
	#define NOW std::chrono::high_resolution_clock::now()

	using TimestampType = std::chrono::time_point<std::chrono::high_resolution_clock>;

	enum class TimeScaleType
	{
		Sec, Min, Hour, Day, Week, Month, Year, None
	};

	static inline float GetTimestampsDifferenceSecs(TimestampType end, TimestampType start)
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 0.001f * 0.001f * 0.001f;
	}

	static inline float ConvertToTimeScale(TimeScaleType scale, float timeVal)
	{
		switch (scale)
		{
		case TimeScaleType::Sec:
			return timeVal;
		case TimeScaleType::Min:
			return timeVal / 60.;
		case TimeScaleType::Hour:
			return timeVal / (60. * 60.);
		case TimeScaleType::Day:
			return timeVal / (60. * 60. * 24);
		case TimeScaleType::Week:
			return timeVal / (60. * 60. * 24 * 7);
		case TimeScaleType::Month:
			return timeVal / (60. * 60. * 24 * 7 * 30);
		case TimeScaleType::Year:
			return timeVal / (60. * 60. * 24 * 7 * 365);
		}
	}
}
