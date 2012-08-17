// Template_Projects.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>
#include "MemoryTracker.h"
#include "StopWatch.h"
#include "List.h"
#include "TestSuite.h"
#include "Exports/BSTree.h"

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
