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


using std::string;

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		TEST_MAIN();
		MemoryTracker mt;
		
		StopWatch t;
		double total = 0;
		for(unsigned int w = 0; w < 10; w++)
		{
			for(unsigned int y = 0; y < 10; y++)
			{
				SortedList<int> sList;
				t.StartTimer();
				for(unsigned int x = 0; x < 10000; x++)
				{
					sList.add( (rand() % 5000) - 2500);
				}
				t.EndTimer();
				std::cout.precision(3);
				total = t.ElapsedTime();
				std::cout << t.ElapsedTime() << std::endl;
			}
			printf("%f took this long\n", total / 10);
			total = 0;
		}

		// memory testors.
		/*
		mt.FirstState();
		mt.SecondState();
		mt.Print(std::cout);
		*/
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
