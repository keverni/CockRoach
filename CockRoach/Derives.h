#pragma once

#include <filesystem>
#include <iostream>
#include <fstream> 

constexpr auto NEED_TO_COPY{ 200 };
static auto g_Counter{ 0 };

static auto g_FilesToCopy{ std::filesystem::current_path() };

static std::ofstream g_LogFile{ "Log.txt" };
