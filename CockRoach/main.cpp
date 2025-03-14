#include <iostream>

import CockRoach;

int main() noexcept
{
	try
	{
		CockRoach::ScanDirectory();
	}
	catch (const std::invalid_argument& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	
	return 0;
}
