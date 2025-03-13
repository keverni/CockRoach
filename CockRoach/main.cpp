#include "Functions.h"

#include <iostream>

int main() noexcept
{
	try
	{
		ScanDirectory("C:\\");
	}
	catch (const std::invalid_argument& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	
	return 0;
}
