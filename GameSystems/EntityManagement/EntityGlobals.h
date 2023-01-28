#pragma once

#include <chrono>

namespace EntityManagement
{
	using Tick = long double;
	using ID = unsigned int;
	using HiResTimeStamp = std::chrono::high_resolution_clock::time_point;

#define HIRES_NOW std::chrono::high_resolution_clock::now()
}