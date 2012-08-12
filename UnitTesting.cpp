#include "TestSuite.h"

#include "List.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
TEST_ADD(SortedList_Removal)
{
	std::vector<int> list1;
	std::vector<int> list2;
	SortedList<int> mainList;
	for(unsigned int x = 1; x < 10; x += 2)
	{
		list1.push_back(x);
		mainList.add(x);
	}
	for(unsigned int x = 0; x < 10; x += 2)
	{
		list2.push_back(x);
		mainList.add(x);
	}

	std::reverse(list2.begin(),list2.end());

}
TEST_ADD(SortedList_MergeTest)
{
	SortedList<int> list1;
	SortedList<int> list2;
	for(unsigned int x = 1; x < 10; x += 2)
	{
		list1.add(x);
	}
	for(unsigned int x = 0; x < 10; x += 2)
	{
		list2.add(x);
	}
	list1.merge(list2);
	for(unsigned int x = 0; x < 10; x++)
	{
		TEST_CONDITION(x == list1[x]);
	}
	TEST_CONDITION(list2.isEmpty() == true);
}
TEST_ADD(SortedList_VectorToSortedList)
{
	std::vector<int> vList;
	for(unsigned int x = 0; x < 10; x++)
	{
		vList.push_back(x);
	}
	SortedList<int> sList(vList);

	for(int x = 0; x < 10; x++)
	{
		TEST_CONDITION(sList[x] == x);
	}
}
TEST_ADD(SortedList_SortedElements)
{

	int randomNum = 10;

	SortedList<int> sList;
	std::vector<int> vList;
	for(int x = 0; x < randomNum; x++)
	{
		int y = (rand() % 5000) - 2500;
		vList.push_back(y);
		sList.add(y);
	}
	std::sort(vList.begin(), vList.end());
	for(int x = 0; x < vList.size(); x++)
	{
		TEST_CONDITION(vList[x] == sList[x]);
	}
}