#pragma once

#include <vector>
#include <exception>


const enum QUE_TYPE
{
	MIN,
	MAX
};

template<typename T>
class PriorityQueue
{
private:
	std::vector<T> pQue;
	// function pointer for pick min priority que or max priority que
	bool (PriorityQueue::*funct)(const T& root, const T& node);

	
	// the min and max compares
	bool minCompare(const T& root, const T& node)
	{
		return root > node;
	}
	bool maxCompare(const T& root, const T& node)
	{
		return root < node;
	}
	void swap(T& t1, T& t2)
	{
		T temp = t1;
		t1 = t2;
		t2 = temp;
	}
	void percolateUp(int index)
	{
		if(index > 0 && (this->*funct)(pQue[(index - 1) / 2], pQue[index]))
		{
			// need a swap
			swap(pQue[index], pQue[(index - 1) / 2]);
			percolateUp((index - 1) / 2);
		}
	}
	void percolateDown(int index)
	{
		int MaxPriority = 0;

		if((2 * index + 2) <= pQue.size() - 1)
		{
			if((this->*funct)(pQue[2 * index + 1], pQue[2 * index + 2]))
			{
				MaxPriority = 2 * index + 2;
			}
			else
			{
				MaxPriority = 2 * index + 1;
			}

			if((this->*funct)(pQue[index], pQue[MaxPriority]))
			{
				swap(pQue[index], pQue[MaxPriority]);
				percolateDown(MaxPriority);
			}

		}
		else if(pQue.size() - 1 == 2 * index + 1) 
		{
			if((this->*funct)(pQue[index], pQue[2 * index + 1])) 
			{
				swap(pQue[index], pQue[2 * index + 1]);
			}
		}
	}
public:
	~PriorityQueue()
	{

	}
	const PriorityQueue& operator=(const PriorityQueue& t)
	{
		if(this != &t)
		{
			funct = t.funct;
			pQue = t.pQue;
		}
		return *this;
	}
	PriorityQueue(const PriorityQueue& t)
	{
		funct = t.funct;
	}
	PriorityQueue()
	{
		funct = &PriorityQueue::maxCompare;
	}
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
	void add(const T& t)
	{
		pQue.push_back(t);
		percolateUp(pQue.size() - 1);
	}
	void add(T && t)
	{
		pQue.push_back(t);
		percolateUp(pQue.size() - 1);
	}
	T pop()
	{
		if(!isEmpty())
		{
			T returner = pQue[0];
			if(pQue.size() != 1)
			{
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