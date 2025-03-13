#include <iostream>

#include "Functions.h"

int main() noexcept
{
	try
	{
		CockRoach::ScanDirectory("C:\\");
	}
	catch (const std::invalid_argument& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	
	return 0;
}
