#pragma once

#include <filesystem>
#include <algorithm>
#include <string>

#define GET_ABSOLUTE_PATH_STRING(path) std::string{ std::filesystem::current_path().string() + path }
