#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// used for testing
#include "testing_tools/TestSuite.h"
#include "testing_tools/MemoryTracker.h"

// containers being tested
#include "containers/BSTree.h"
#include "containers/sorted_list.h"
#include "containers/TreapTree.h"
#include "containers/PriorityQueue.h"
#include "containers/LinkedList.h"
#include "containers/DoublylinkedList.h"
#include "containers/content_tree.h"
#include "containers/hash_table.h"
// using the class for complex add tests
class testingClass
{
private:
	int a;
public:
	const testingClass& operator=(const testingClass& t);
	bool operator<(const testingClass& b)
	{
		return a < b.a;
	}
	bool operator>(const testingClass& b)
	{
		return a > b.a;
	}
};
/*
namespace doublylinkedlist
{
	TEST_ADD(DoublyLinkedList_PrimitiveAdd)
	{

	}
	TEST_ADD(DoublyLinkedList_ComplexAdd)
	{

	}
	TEST_ADD(DoublyLinkedList_Remove)
	{

	}
	TEST_ADD(DoublyLinkedList_MemLeak)
	{

	}
	TEST_ADD(DoublyLinkedList_Copy)
	{

	}
	TEST_ADD(DoublyLinkedList_Itorators)
	{

	}
	TEST_ADD(DoublyLinkedList_Size)
	{

	}
};*/
// LinkedList Unit Testing
namespace linklist
{
	// #TODO need to add test for faults 
	TEST_ADD(LinkedList_AddPrimitiveElements)
	{
		LinkedList<int> list;

		for(unsigned int x = 0; x < 100; x++)
		{
			list.push_front(x);
		}
		TEST_CONDITION(list.size() == 100);
		list.clear();
		for(unsigned int x = 0; x < 100; x++)
		{
			list.push_back(x);
		}
		TEST_CONDITION(list.size() == 100);
	}
	TEST_ADD(LinkedList_Constructers)
	{
		LinkedList<int> g;
		for(unsigned int x = 0; x < 10; x++)
		{
			g.push_back(x);
		}

		LinkedList<int> f(g.begin() + 2);
		g.clear();
		LinkedList<int> h;
		h = f;
		f.clear();
		LinkedList<int> i(h);


	}
	TEST_ADD(LinkedList_MemLeak)
	{
		MemoryTracker tracker;
		LinkedList<int> list;
		tracker.FirstState();
		
		for(unsigned int x = 0; x < 100; x++)
		{
			list.push_front(x);
		}
		list.clear();
		tracker.SecondState();
		TEST_CONDITION(tracker.NormalBlocks() ==0);


		tracker.FirstState();
		LinkedList<int>* list2 = new LinkedList<int>;
		for(unsigned int x = 0;x < 10; x++)
		{
			list2->push_front(x);
		}
		delete list2;
		tracker.SecondState();
		TEST_CONDITION(tracker.NormalBlocks() == 0);
	}
	TEST_ADD(LinkedList_Copy)
	{
		LinkedList<int>* list = new LinkedList<int>();
		for(unsigned int x = 0; x < 10; x++)
		{
			list->push_back(x);
		}
		LinkedList<int> list2 = *list;
		list->clear();
	
		TEST_CONDITION(list2.back() == 9 && list2.front() == 0);
	}
	TEST_ADD(LinkedList_Removing)
	{
		LinkedList<int> list;

		for(unsigned int x = 0; x < 10; x++)
		{
			list.push_front(x);
		}

		for(unsigned int x = 0; x < 10; x++)
		{
			TEST_CONDITION(list.front() ==  9 - x);
			list.pop_front();
		}
		for(unsigned int x = 0; x < 10; x++)
		{
			list.push_front(x);
		}
		for(unsigned int x = 0; x < 10; x++)
		{
			TEST_CONDITION(list.back() == x);
			list.pop_back();
		}
		TEST_CONDITION(list.empty());
	}
	TEST_ADD(LinkedList_ComplexElements)
	{

	}
	TEST_ADD(LinkedList_Itorators)
	{
		LinkedList<int> list;

		for(unsigned int x = 0; x < 10; x++)
		{
			list.push_front(x);
		}
		int counter = 0;
		for(LinkedList<int>::forward_iterator itor = list.begin(); itor != list.end(); itor++)
		{
			counter++;
		}
		TEST_CONDITION(counter == 10);
	}
	TEST_ADD(LinkedList_Size)
	{
		LinkedList<int> list;
		for(unsigned int x = 0; x < 10; x++)
		{
			list.push_back(x);
		}
		for(unsigned int x = 0; x < 10; x++)
		{
			list.push_front(x);
		}

		TEST_CONDITION(list.size() == 20);

		list.pop_front();
		list.pop_front();
		list.pop_front();
		TEST_CONDITION(list.size() == 17);
	}
	TEST_ADD(LinkedList_find)
	{
		LinkedList<int> g;
		g.push_back(3);
		g.push_back(9);
		g.push_back(6);
		g.push_back(2);
		LinkedList<int>::forward_iterator i = g.find(4);
		TEST_CONDITION(g.find(4).valid() == false);

	}
};
/*
// PriorityQueue Unit Testing
namespace priorityqueue
{
	TEST_ADD(PriorityQueue_MinQue)
	{
		PriorityQueue<int> pQue(MIN);
		sorted_vector<int> sList;
	
		for(unsigned int x = 0; x < 1000; x++)
		{
			int y = (rand() % 5000) - 2500;
			pQue.add(y);
			sList.push(y);
		}
		for(unsigned int x = 0; x < sList.size(); x++)
		{		
			TEST_CONDITION(pQue.pop() == sList[x]);
		}
	}
	TEST_ADD(PriorityQueue_AddPrimitiveElements)
	{
		PriorityQueue<int> pQue;
		sorted_vector<int> sList;
		for(unsigned int x = 0; x < 1000; x++)
		{
			int y = (rand() % 5000) - 2500;
			pQue.add(y);
			sList.push(y);
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
}
// TreapTree Unit Testing
namespace treaptree
{
	TEST_ADD(TreapTree_AddPrimitiveElements)
	{
		TreapTree<int> tTree;
		std::vector<int> sList;
		for(unsigned int x = 0; x < 100; x++)
		{
			int y = (rand() % 5000) - 2500;
			tTree.add(y);
			sList.push_back(y);
		}

		for(unsigned int x = 0; x < sList.size(); x++)
		{		
			TEST_CONDITION(tTree.find(sList[x]) != nullptr);
		}
	}
	TEST_ADD(TreapTree_MemLeak)
	{
		MemoryTracker memtrack;
		memtrack.FirstState();
		TreapTree<int>* testTree = new TreapTree<int>;
		for(unsigned int x = 0; x < 100; x++)
		{
			testTree->add(x);
		}
		delete testTree;
		memtrack.SecondState();

		TEST_CONDITION(memtrack.NormalBlocks() == 0);
	}
	TEST_ADD(TreapTree_RemoveElements)
	{
		TreapTree<int> tTree;
		sorted_vector<int> sList;
		for(unsigned int x = 0; x < 1000; x++)
		{
			int y = (rand() % 5000) - 2500;
			tTree.add(y);
			sList.push(y);
		}
		for(unsigned int x = 0; x < sList.size(); x++)
		{
			tTree.remove(sList[x]);
		}
		int x = 0;
	}
	TEST_ADD(TreapTree_SizeTest)
	{
		TreapTree<int> testTree;
		for(unsigned int x = 0; x < 10; x++)
		{
			testTree.add(x);
		}
		TEST_CONDITION(testTree.size() == 10)
	}
	TEST_ADD(TreapTree_CopyConstructors)
	{
	
	}
	TEST_ADD(TreapTree_AddComplexElements)
	{

	}
};
// Binary Tree Unit Testing
namespace bstree
{
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
		sorted_vector<int> sList;
		for(int x = 0; x < 50; x++)
		{
			int randNum = (int)rand() % 1000 - 500;
			tree.add(randNum);
			sList.push(randNum);
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
		sorted_vector<int> sList;
		for(unsigned int x = 0; x < 10; x++)
		{
			sList.push(arr[x]);
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
		sorted_vector<int> sList;
		for(int x = 0; x < 10; x++)
		{
			int randNum = (int)rand()% 1000 - 500;
			firstTree->add(randNum);
			sList.push(randNum);
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
};
*/

// Sorted List unit testing
namespace sortedlist
{
	TEST_ADD(sorted_vector_MemLeak)
	{
		MemoryTracker memTrace;
		memTrace.FirstState();
		sorted_vector<int>* mainList = new sorted_vector<int>();
		for(unsigned int x = 1; x < 10; x += 2)
		{
			mainList->push(x);
		}
		delete mainList;
		memTrace.SecondState();
		TEST_CONDITION(memTrace.NormalBlocks() == 0);
	}
	TEST_ADD(sorted_vector_Removal)
	{
		std::vector<int> list1;
		std::vector<int> list2;
		sorted_vector<int> firstList;
		for(unsigned int x = 0; x < 10; x++)
		{
			list1.push_back(x);
			firstList.push(x);
		}
		sorted_vector<int> secondList = firstList;
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
	TEST_ADD(sorted_vector_MergeTest)
	{
		sorted_vector<int> list1;
		sorted_vector<int> list2;
		for(unsigned int x = 1; x < 10; x += 2)
		{
			list1.push(x);
		}
		for(unsigned int x = 0; x < 10; x += 2)
		{
			list2.push(x);
		}
		list1.merge(list2);
		for(unsigned int x = 0; x < 10; x++)
		{
			TEST_CONDITION(x == list1[x]);
		}
		TEST_CONDITION(list2.isEmpty() == true);

		std::vector<int> list3;
		std::vector<int> list4;
		sorted_vector<int> sList;
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
	TEST_ADD(sorted_vector_VectorTosorted_vector)
	{
		std::vector<int> vList;
		for(unsigned int x = 0; x < 10; x++)
		{
			vList.push_back(x);
		}
		sorted_vector<int> sList(vList);

		for(int x = 0; x < 10; x++)
		{
			TEST_CONDITION(sList[x] == x);
		}
	}
	TEST_ADD(sorted_vector_AddComplexElements)
	{
	
	}
	TEST_ADD(sorted_vector_AddPrimativeElements)
	{
		int randomNum = 10;

		sorted_vector<int> sList;
		std::vector<int> vList;
		for(int x = 0; x < randomNum; x++)
		{
			int y = (rand() % 5000) - 2500;
			vList.push_back(y);
			sList.push(y);
		}
		std::sort(vList.begin(), vList.end());
		for(unsigned int x = 0; x < vList.size(); x++)
		{
			TEST_CONDITION(vList[x] == sList[x]);
		}
	}
	TEST_ADD(sorted_vector_PointerSort)
	{
		sorted_vector<int*, pointer_compare_int<int*>> sorted_list;
		sorted_list.push(new int(3));
		sorted_list.push(new int(2));
		sorted_list.push(new int(10));
		sorted_list.push(new int(-5));
		sorted_list.push(new int(9));
		sorted_list.push(new int(1));
		int* d = new int(4);

		sorted_list.positionOf(d);
	}
};
namespace hashtable
{
	TEST_ADD(hashtable_removeelements)
	{

	}
	TEST_ADD(hashtable_addelements)
	{

	}
	TEST_ADD(hashtable_complex)
	{

	}
	TEST_ADD(hashtable_copy)
	{

	}
	TEST_ADD(hashtable_find)
	{
		
	}
	TEST_ADD(hashtable_memtest)
	{
		MemoryTracker mem;
		mem.FirstState();
		hash_table<int>* h = new hash_table<int>(40);

		for(unsigned int x = 0; x < 100; x++)
		{
			h->add((int)rand() % 100);
		}
		h->rehash(5);
		h->print_table();
		delete h;

		mem.SecondState();

		TEST_CONDITION(mem.NormalBlocks() == 0);


	}
};
namespace contenttree
{

};