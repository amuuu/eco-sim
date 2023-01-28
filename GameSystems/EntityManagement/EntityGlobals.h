#pragma once

#include <chrono>

namespace EntityManagement
{
	using Tick = long double;
	using EntityId = unsigned int;
	using HiResTimeStamp = std::chrono::high_resolution_clock::time_point;

#define HI_RES_NOW std::chrono::high_resolution_clock::now()
}