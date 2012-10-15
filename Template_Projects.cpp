// Template_Projects.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include "testing tools/TestSuite.h"
#include "containers/BSTree.h"
#include "testing tools/MemoryTracker.h"
#include "designs/abstract_factory.h"


class ff : public virtual factory::BaceProcessFactory<std::string>
{

};

int _tmain(int argc, _TCHAR* argv[])
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
