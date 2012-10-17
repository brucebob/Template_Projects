#include <iostream>
#include <string>
#include "UnitTesting.h"

int main(int argc, char* argv[])
{
	try
	{
		TEST_MAIN();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}