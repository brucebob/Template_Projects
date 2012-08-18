#pragma once

#include <vector>
#include <exception>

/*
*		Priority Queue
*		for complex elements must have a working 
*		operator < > and = 
*		since it's used to find priority and swap positions
*/

// uses this enum to pick which QUE_TYPE
const enum QUE_TYPE
{
	MIN,
	MAX
};

template<typename T>
class PriorityQueue
{
private:
	// vector of the T which is turned into a queue
	std::vector<T> pQue;
	// function pointer for setting min and max function
	bool (PriorityQueue::*funct)(const T& root, const T& node);

	// the min and max compares used for the function pointer
	bool minCompare(const T& root, const T& node)
	{
		return root > node;
	}
	bool maxCompare(const T& root, const T& node)
	{
		return root < node;
	}
	// makes a single copy and swap two elements
	void swap(T& t1, T& t2)
	{
		T temp = t1;
		t1 = t2;
		t2 = temp;
	}
	// takes a index and see if left or right based on a array based tree
	// (index - 1 ) / 2 is the parent of index
	// make sure there more then one element
	void percolateUp(int index)
	{
		if(index > 0 && (this->*funct)(pQue[(index - 1) / 2], pQue[index]))
		{
			// need a swap since index has a higher priority then (index - 1) / 2
			swap(pQue[index], pQue[(index - 1) / 2]);
			// checks to see if the new parent needs to move up more
			percolateUp((index - 1) / 2);
		}
	}
	// move index down 
	// based on the left and right of the parent
	// which is 2 * index + 2 for right
	// 2 * index + 1 for left
	void percolateDown(int index)
	{
		if((2 * index + 2) <= pQue.size() - 1)
		{
			int MaxPriority = 0;
			// finds highest priority left or right
			if((this->*funct)(pQue[2 * index + 1], pQue[2 * index + 2]))
			{
				MaxPriority = 2 * index + 2;
			}
			else
			{
				MaxPriority = 2 * index + 1;
			}
			// then checks if it's higher then the index
			if((this->*funct)(pQue[index], pQue[MaxPriority]))
			{
				swap(pQue[index], pQue[MaxPriority]);
				percolateDown(MaxPriority);
			}

		}
		// checks to see if only the left node 2 * index + 1
		else if(pQue.size() - 1 == 2 * index + 1) 
		{
			if((this->*funct)(pQue[index], pQue[2 * index + 1])) 
			{
				swap(pQue[index], pQue[2 * index + 1]);
			}
		}
	}
public:
	// since vector does it's own deleting nothing need to be removed
	~PriorityQueue()
	{

	}
	// deep copy of operator=()
	// sets the QUE_TYPE and copies the queue
	const PriorityQueue& operator=(const PriorityQueue& t)
	{
		if(this != &t)
		{
			if(t.funct == & maxCompare)
			{
				funct = &PriorityQueue::maxCompare;
			}
			else
			{
				funct = &PriorityQueue::minCompare;
			}
			pQue = t.pQue;
		}
		return *this;
	}
	// constructor taking a priority queue 
	// sets the QUE_TYPE and copies the list
	PriorityQueue(const PriorityQueue& t)
	{
		if(t.funct == & maxCompare)
		{
			funct = &PriorityQueue::maxCompare;
		}
		else
		{
			funct = &PriorityQueue::minCompare;
		}
		pQue = t.pQue;
	}
	// default constructor with max compare
	PriorityQueue()
	{
		funct = &PriorityQueue::maxCompare;
	}
	// constructor with picking the MIN or MAX queue
	PriorityQueue(QUE_TYPE qt)
	{
		switch(qt)
		{
		case MAX:
			{
				funct = &PriorityQueue::maxCompare;
				break;
			}
		case MIN:
			{
				funct = &PriorityQueue::minCompare;
			}
		}
	}
	// adds a element to the queue
	// percolate up based on the priority
	void add(const T& t)
	{
		pQue.push_back(t);
		percolateUp(pQue.size() - 1);
	}
	// adds a element to the queue
	// percolate up based on the priority
	void add(T && t)
	{
		pQue.push_back(t);
		percolateUp(pQue.size() - 1);
	}
	// pops the highest priority and returns it after it fixes the queue
	// throws if the queue is empty
	T pop()
	{
		if(!isEmpty())
		{
			// makes a copy of the return element
			T returner = pQue[0];
			// checks to see if it's the only element
			if(pQue.size() != 1)
			{
				// moves the last element to 0
				// then percolate down till the highest priority is at 0
				pQue[0] = pQue[pQue.size() - 1];
				pQue.pop_back();
				percolateDown(0);
			}
			else
			{
				pQue.pop_back();
			}
			return returner;
		}
		else
		{
			throw std::exception("PriorityQueue: empty queue");
		}
	}
	// return the front of the queue 
	// the front is immutable since it could edit the priority
	// throws if empty
	const T& front() const
	{
		if(!isEmpty())
		{
			return pQue[0];
		}
		else
		{
			throw std::exception("PriorityQueue: empty queue");
		}
	}
	bool isEmpty() const
	{
		return pQue.empty();
	}
};