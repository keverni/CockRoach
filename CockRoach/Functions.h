#pragma once

#include "Derives.h"

#include <iostream>
#include <filesystem>
#include <string>
#include <stdexcept>

namespace fs = std::filesystem;

bool CheckValid(const fs::directory_entry& object)
{
	if (object.is_directory())
	{
		if ((object.status().permissions() & std::filesystem::perms::owner_write) != std::filesystem::perms::none)
		{
			return true;
		}
	}
	return false;
}

void ScanDirectory(const std::string& start_directory = fs::current_path().generic_string(), const fs::path& from_copy = g_FilesToCopy)
{	
	if (fs::exists(start_directory))
	{
		try
		{
			fs::directory_iterator directory_iter{ start_directory };

			for (const auto& elem : directory_iter)
			{
				if (CheckValid(elem))
				{
					if (g_Counter == NEED_TO_COPY)
					{
						fs::copy(from_copy, elem.path());
						g_LogFile << elem.path() << "\n";

						g_Counter = 0;
						continue;
					}
					else
					{
						++g_Counter;
						ScanDirectory(elem.path().generic_string());
					}	
				}			
			}
		}
		catch (const std::exception& ex)
		{
			return;
		}
	}
	else
	{
		throw std::invalid_argument("Directory is not found!");
	}
}
