# CockRoach
CockRoach - Educational and just-for-fun project on С++

This is a project that recursively goes through directories that have write access, and leaves a copy of itself every 200 directories (Later, I will also add that the program also runs the newly created copy)
**The project is purely educational and non-working (Antivirus does not allow it to start)**

# Example

```cpp
int main() noexcept
{
	try
	{
		ScanDirectory("C:\\start_of_recursion_scan\\", "C:\\copy_from");
	}
	catch (const std::invalid_argument& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	
	return 0;
}
```
