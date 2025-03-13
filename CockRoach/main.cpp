#include "Functions.h"

int main() noexcept
{
	try
	{
		ScanDirectory("C:/");
	}
	catch (const std::invalid_argument& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	return 0;
}
