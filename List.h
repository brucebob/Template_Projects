#pragma once

#include <vector>
#include <exception>
/*
*	SortedList<T>
*	To Use this list on non-Primitives you need to overload the < > of the class
*   for it to be able to sort the elements T
*/
template<typename T> class SortedList
{
private:
	std::vector<T> _list;
public:
	~SortedList()
	{

	}
	SortedList<T>()
	{

	}
	// takes in a vector<T> and sorts it's data content to a SortedList<T>
	SortedList<T>(const std::vector<T>& vList)
	{
		for(std::vector<T>::const_iterator itor = vList.cbegin(); itor != vList.cend(); itor++)
		{
			add(*itor);
		}
	}
	// copy constructor of a vector<T> 
	const SortedList& operator=(const std::vector<T>& vList)
	{
		_list.clear();
		for(std::vector<T>::const_iterator itor = vList.cbegin(); itor != vList.cend(); itor++)
		{
			add(*itor);
		}
		return *this;
	}
	// copy constructor
	SortedList<T>(const SortedList& listIn)
	{
		_list = listIn._list;
	}
	// copy constructor
	const SortedList& operator=(const SortedList& listIn)
	{
		if(this != &listIn)
		{
			_list = listIn._list;
		}
		return *this;
	}
	// returns a ref value of the point at spot
	// throw if out of bounds
	T& operator[](unsigned int spot)
	{
		if(spot < _list.size())
		{
			return _list[spot];
		}
		else
		{
			throw std::out_of_range("Number inputed is out of range.");
		}
	}
	// returns a const ref value at point spot
	// throws if out of bounds
	const T& operator[](unsigned int spot) const
	{
		if(spot < _list.size())
		{
			return _list[spot];
		}
		else
		{
			throw std::out_of_range("Number inputed is out of range.");
		}
	}
	// empties the list to 0 elements
	void clear()
	{
		_list.clear();
	}
	// takes in a r value ref and adds it to the container
	void add(T && t)
	{
		// use binary search to find where the next element should be inserted keeps it O(log(n))
		unsigned int start = 0, end = _list.size();
		while(start < end)
		{
			unsigned int mid = (end + start) / 2;
			if(_list[mid] > t)
			{
				end = mid;
			}
			else if(_list[mid] < t)
			{
				start = mid + 1;
			}
			else
			{
				_list.insert(_list.begin() + mid, t);
				return;
			}
		}
		_list.insert(_list.begin() + start, t);
	}
	// takes a const T and adds it to the container
	void add(const T& t)
	{
		// use binary search to find where the next element should be inserted keeps it O(log(n))
		unsigned int start = 0, end = _list.size();
		while(start < end)
		{
			unsigned int mid = (end + start) / 2;
			if(_list[mid] > t)
			{
				end = mid;
			}
			else if(_list[mid] < t)
			{
				start = mid + 1;
			}
			else
			{
				_list.insert(_list.begin() + mid, t);
				return;
			}
		}
		_list.insert(_list.begin() + start, t);	
	}
	// uses binary search to find the element needed returns position if found
	// returns -1 if not found 
	template<typename TT>
	const int positionOf(const TT& t)
	{
		if(_list.empty())
		{
			return -1;
		}
		else
		{
			// uses binary search to find the element T
			unsigned int start = 0;
			unsigned int end = _list.size();
			while(start < end)
			{
				unsigned int mid = (end + start) / 2;
				if(_list[mid] > t)
				{
					end = mid;
				}
				else if(_list[mid] < t)
				{
					start = mid + 1;
				}
				else
				{
					return mid;
				}
			}
			return -1;
		}
	}
	// takes in a SortedList and empties the list after it's been added
	void merge(SortedList<T>& t)
	{
		std::vector<T> newList;		
		unsigned int x = 0;
		unsigned int y = 0;
		while(x < _list.size() || y < t.size())
		{ 
			if(x == _list.size() || y == t.size())
			{
				break;
			}
			if(_list[x] > t[y])
			{
				newList.push_back(t[y++]);
			}
			else if (_list[x] < t[y])
			{
				newList.push_back(_list[x++]);
			}
		}
		while(x != _list.size())
		{
			newList.push_back(_list[x++]);
		}
		while(y != t.size())
		{
			newList.push_back(t[y++]);
		}

		t.clear();
		_list = newList;
	}
	// takes vector<T> and adds it to Sorted List and clears the vector
	void merge(std::vector<T>& t)
	{
		for(std::vector<T>::iterator itor = t.begin(); itor != t.end(); itor++)
		{
			add(*itor);
		}
		t.clear();
	}
	// remove a element at index spot
	// throws if out of bounds
	void removeAtIndex(const unsigned int spot)
	{
		if(spot < _list.size())
		{
			_list.erase(_list.begin() + spot);
		}
		else
		{
			throw std::out_of_range("removeAtIndex: Number inputed is out of range.");
		}
	}
	// searches the Sorted List if element is found it's removed else does nothing.
	template<typename TT>
	void remove(const TT& t)
	{
		int spot = positionOf(t);
		if(spot != -1)
		{
			_list.erase(_list.begin() + spot);
		}
	}
	// return the size of the sorted list
	const unsigned int size() const
	{
		return _list.size();
	}
	// returns if the Sorted List is empty
	bool isEmpty() const
	{
		return _list.empty();
	}
};