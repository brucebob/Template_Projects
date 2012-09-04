#include "TestSuite.h"
#include "MemoryTracker.h"


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Exports\BSTree.h"
#include "List.h"
#include "TreapTree.h"
#include "PriorityQueue.h"


// using the class for complex add tests
class testingClass
{
private:

public:

};

// PriorityQueue Unit Testing
TEST_ADD(PriorityQueue_MinQue)
{
	PriorityQueue<int> pQue(MIN);
	SortedList<int> sList;
	
	for(unsigned int x = 0; x < 1000; x++)
	{
		int y = (rand() % 5000) - 2500;
		pQue.add(y);
		sList.add(y);
	}
	for(unsigned int x = 0; x < sList.size(); x++)
	{		
		TEST_CONDITION(pQue.pop() == sList[x]);
	}
}
TEST_ADD(PriorityQueue_AddPrimitiveElements)
{
	PriorityQueue<int> pQue;
	SortedList<int> sList;
	for(unsigned int x = 0; x < 1000; x++)
	{
		int y = (rand() % 5000) - 2500;
		pQue.add(y);
		sList.add(y);
	}
	
	for(unsigned int x = sList.size(); x > 0; x--)
	{		
		TEST_CONDITION(pQue.pop() == sList[x - 1]);
	}
}
TEST_ADD(PriorityQueue_MemLeak)
{
	
	MemoryTracker memTrace;
	memTrace.FirstState();
	PriorityQueue<int>* pQue = new PriorityQueue<int>();
	for(unsigned int x = 10; x < 10; x++)
	{
		pQue->add(x);
	}
	delete pQue;
	memTrace.SecondState();

	TEST_CONDITION(memTrace.NormalBlocks() == 0);
}
TEST_ADD(PriorityQueue_AddComplexElements)
{
	
}
TEST_ADD(PriorityQueue_CopyConstructor)
{

}
// TreapTree Unit Testing
TEST_ADD(TreapTree_RemoveElements)
{

}
TEST_ADD(TreapTree_MemLeak)
{

}
TEST_ADD(TreapTree_AddElements)
{

}
// Binary Tree Unit Testing
TEST_ADD(BSTree_SizeTest)
{
	BSTree<int> tree;

	while(tree.size() != 20)
	{
		tree.add(rand() % 5000-2500);
	}
}
TEST_ADD(BSTree_MinAndMax)
{
	BSTree<int> tree;
	SortedList<int> sList;
	for(int x = 0; x < 50; x++)
	{
		int randNum = (int)rand() % 1000 - 500;
		tree.add(randNum);
		sList.add(randNum);
	}
	TEST_CONDITION(*tree.minElement() == sList[0]);
	TEST_CONDITION(*tree.maxElement() == sList[sList.size() - 1]);
}
TEST_ADD(BSTree_RemoveNodes)
{
	
	int arr[10] = 
	{
		    4,
	   2,        6,
	1,    3,   5,  7,
  0,                 10,
                  9

};
	SortedList<int> sList;
	for(unsigned int x = 0; x < 10; x++)
	{
		sList.add(arr[x]);
	}
	

	MemoryTracker memTrace;
	memTrace.FirstState();

	BSTree<int>* tree = new BSTree<int>();
	for(unsigned int x = 0; x < 10; x++)
	{
		tree->add(arr[x]);
	}
	
	for(unsigned int x = 0; x < sList.size(); x++)
	{
		TEST_CONDITION(tree->removeElement(sList[x]) == true);
	}
	TEST_CONDITION(tree->isEmpty() == true);
	delete tree;
	memTrace.SecondState();
	TEST_CONDITION(memTrace.NormalBlocks() == 0);
}
TEST_ADD(BSTree_AddComplexElements)
{

}
TEST_ADD(BSTree_AddPrimativeElements)
{
	std::vector<int> vList;
	BSTree<int> bsTree;
	for(int x = 0; x < 100; x++)
	{
		int y = (rand() % 5000) - 2500;
		vList.push_back(y);
		bsTree.add(y);
	}

	for(unsigned int x = 0; x < 10; x++)
	{
		TEST_CONDITION(bsTree.findElement(vList[x]) != nullptr);
	}
}
TEST_ADD(BSTree_memLeak)
{
	MemoryTracker memTrace;
	memTrace.FirstState();
	BSTree<int>* bsTree = new BSTree<int>();
	for(int x = 0; x < 100; x++)
	{
		int y = (rand() % 5000) - 2500;
		bsTree->add(y);
	}
	delete bsTree;
	memTrace.SecondState();
	TEST_CONDITION(memTrace.NormalBlocks() == 0);
}
TEST_ADD(BSTree_CopyConstruct)
{
	BSTree<int>* firstTree = new BSTree<int>();
	SortedList<int> sList;
	for(int x = 0; x < 10; x++)
	{
		int randNum = (int)rand()% 1000 - 500;
		firstTree->add(randNum);
		sList.add(randNum);
	}

	const BSTree<int> secondTree(*firstTree);
	delete firstTree;
	for(unsigned int x = 0; x < sList.size(); x++)
	{
		TEST_CONDITION(sList[x] == *secondTree.findElement(sList[x]));
	}

	BSTree<int> thirdTree;
	for(int x = 0; x < 10; x++)
	{
		int randNum = (int)rand()% 1000 - 500;
		thirdTree.add(randNum);
	}
	thirdTree = secondTree;
}
// Sorted List unit testing
TEST_ADD(SortedList_MemLeak)
{
	MemoryTracker memTrace;
	memTrace.FirstState();
	SortedList<int>* mainList = new SortedList<int>();
	for(unsigned int x = 1; x < 10; x += 2)
	{
		mainList->add(x);
	}
	delete mainList;
	memTrace.SecondState();
	TEST_CONDITION(memTrace.NormalBlocks() == 0);
}
TEST_ADD(SortedList_Removal)
{
	std::vector<int> list1;
	std::vector<int> list2;
	SortedList<int> firstList;
	for(unsigned int x = 0; x < 10; x++)
	{
		list1.push_back(x);
		firstList.add(x);
	}
	SortedList<int> secondList = firstList;
	std::reverse(list1.begin(), list1.end());
	for(std::vector<int>::iterator itor = list1.begin(); itor != list1.end(); itor++)
	{
		firstList.remove(*itor);
	}
	TEST_CONDITION(firstList.size() == 0);
	for(unsigned int x = list1.size(); x > 0; x--)
	{
		secondList.removeAtIndex(x - 1);
	}
	TEST_CONDITION(secondList.size() == 0);
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

	std::vector<int> list3;
	std::vector<int> list4;
	SortedList<int> sList;
	for(unsigned int x = 1; x < 10; x += 2)
	{
		list3.push_back(x);
	}
	for(unsigned int x = 0; x < 10; x += 2)
	{
		list4.push_back(x);
	}
	sList.merge(list3);
	sList.merge(list4);
	for(unsigned int x = 0; x < 10; x++)
	{
		TEST_CONDITION(x == sList[x]);
	}
	TEST_CONDITION(list3.size() == 0 && list4.size() == 0);
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
TEST_ADD(SortedList_AddComplexElements)
{
	
}
TEST_ADD(SortedList_AddPrimativeElements)
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
	for(unsigned int x = 0; x < vList.size(); x++)
	{
		TEST_CONDITION(vList[x] == sList[x]);
	}
}