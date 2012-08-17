#pragma once

#include <vector>
#include <exception>

template<typename T>
class PriorityQueue
{
private:
	std::vector<T> pQue;
	// function pointer for pick min priority que or max priority que
	bool (*funct)(const T& root, const T& node);
	// the min and max compares
	bool minCompare(const T& root, const T& node)
	{
		return root < node;
	}
	bool maxCompare(const T& root, const T& node)
	{
		return root > node;
	}

	void percolateUp(int spot, bool (*functors)(const T& root, const T& node))
	{
		if(spot > 0 && (*functors)(pQue[(spot - 1) / 2], pQue[spot]))
		{
			percolateUp((spot - 1) / 2, functors);
		}
	}
	void percolateDown(int spot, bool (*functors)(const T& root, const T& node))
	{

	}
public:
	const static enum QUE_TYPE
	{
		MIN,
		MAX
	};
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
		funct = maxCompare;
	}
	PriorityQueue(enum QUE_TYPE qt)
	{
		switch(qt)
		{
		case MAX:
			{
				funct = maxCompare;
				break;
			}
		case MIN:
			{
				funct = minCompare;
			}
		}
	}
	void add(const T& t)
	{
		pQue.push_back(t);
		percolateUp(pQue.size(), funct);
	}
	void add(T && t)
	{
		pQue.push_back(t);
		percolateUp(pQue.size(), funct);
	}
	t& pop()
	{
		if(!isEmpty)
		{
			T returner = pQue[0];
			if(pQue.size() != 1)
			{
				pQue[0] = pQue[pQue.size() - 1];
				pQue.pop_back();
				percolateDown(0, funct);
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
	t& front() const
	{
		if(!isEmpty)
		{

		}
		else
		{
			throw std::exception("PriorityQueue: empty queue");
		}
	}
	bool isEmpty()
	{
		return pQue.empty();
	}
};