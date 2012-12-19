#pragma once

#include <vector>
#include <exception>
#include "compare_function.h"
/*
*	sorted_vector<T>
*	To Use this list on non-Primitives you need to overload the < > of the class
*   for it to be able to sort the elements T
*/
template<typename T, typename F = compare_int<T>> 
class sorted_vector
{
private:
	std::vector<T> data_list;
public:
	~sorted_vector()
	{

	}
	sorted_vector()
	{
		
	}
	// takes in a vector<T> and sorts it's data content to a sorted_vector<T>
	sorted_vector(const std::vector<T>& vList)
	{
		for(std::vector<T>::const_iterator itor = vList.cbegin(); itor != vList.cend(); itor++)
		{
			push(*itor);
		}
	}
	// copy constructor of a vector<T> 
	const sorted_vector& operator=(const std::vector<T>& vList)
	{
		data_list.clear();
		for(std::vector<T>::const_iterator itor = vList.cbegin(); itor != vList.cend(); itor++)
		{
			add(*itor);
		}
		return *this;
	}
	// copy constructor
	sorted_vector(const sorted_vector& listIn)
	{
		data_list = listIn.data_list;
	}
	// copy constructor
	const sorted_vector& operator=(const sorted_vector& listIn)
	{
		if(this != &listIn)
		{
			data_list = listIn.data_list;
		}
		return *this;
	}
	// returns a ref value of the point at spot
	// throw if out of bounds
	T& operator[](unsigned int spot)
	{
		if(spot < data_list.size())
		{
			return data_list[spot];
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
		if(spot < data_list.size())
		{
			return data_list[spot];
		}
		else
		{
			throw std::out_of_range("Number inputed is out of range.");
		}
	}
	// empties the list to 0 elements
	void clear()
	{
		data_list.clear();
	}
	// takes in a universal ref and adds it to the container
	void push(T && t)
	{
		// use binary search to find where the next element should be inserted keeps it O(log(n))
		unsigned int start = 0, end = data_list.size();
		while(start < end)
		{
			unsigned int mid = (end + start) / 2;
			int next_position = F()(t, data_list[mid]);
			if(next_position == -1)
			{
				end = mid;
			}
			else if(next_position == 1)
			{
				start = mid + 1;
			}
			else
			{
				data_list.insert(data_list.begin() + mid, t);
				return;
			}
		}
		data_list.insert(data_list.begin() + start, t);
	}
	// takes a const T and adds it to the container
	void push(const T& t)
	{
		// use binary search to find where the next element should be inserted keeps it O(log(n))
		unsigned int start = 0, end = data_list.size();
		while(start < end)
		{
			unsigned int mid = (end + start) / 2;
			int next_position = F()(t, data_list[mid]);
			if(next_position == -1)
			{
				end = mid;
			}
			else if(next_position == 1)
			{
				start = mid + 1;
			}
			else
			{
				data_list.insert(data_list.begin() + mid, t);
				return;
			}
		}
		data_list.insert(data_list.begin() + start, t);	
	}
	// uses binary search to find the element needed returns position if found
	// returns -1 if not found 
	template<typename TT>
	const int positionOf(const TT& t)
	{
		if(data_list.empty())
		{
			return -1;
		}
		else
		{
			// uses binary search to find the element T
			unsigned int start = 0;
			unsigned int end = data_list.size();
			while(start < end)
			{
				unsigned int mid = (end + start) / 2;
				int next_position = F()(t, data_list[mid]);
				if(next_position == -1)
				{
					end = mid;
				}
				else if(next_position == 1)
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
	// takes in a sorted_vector and empties the list after it's been added
	void merge(sorted_vector& t)
	{
		std::vector<T> newList;		
		unsigned int x = 0;
		unsigned int y = 0;
		while(x < data_list.size() || y < t.size())
		{ 
			if(x == data_list.size() || y == t.size())
			{
				break;
			}
			if(data_list[x] > t[y])
			{
				newList.push_back(t[y++]);
			}
			else if (data_list[x] < t[y])
			{
				newList.push_back(data_list[x++]);
			}
		}
		while(x != data_list.size())
		{
			newList.push_back(data_list[x++]);
		}
		while(y != t.size())
		{
			newList.push_back(t[y++]);
		}

		t.clear();
		data_list = newList;
	}
	// takes vector<T> and adds it to Sorted List and clears the vector
	void merge(std::vector<T>& t)
	{
		for(std::vector<T>::iterator itor = t.begin(); itor != t.end(); itor++)
		{
			push(*itor);
		}
		t.clear();
	}
	// remove a element at index spot
	// throws if out of bounds
	void removeAtIndex(const unsigned int spot)
	{
		if(spot < data_list.size())
		{
			data_list.erase(data_list.begin() + spot);
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
			data_list.erase(data_list.begin() + spot);
		}
	}
	// return the size of the sorted list
	const unsigned int size() const
	{
		return data_list.size();
	}
	// returns if the Sorted List is empty
	bool isEmpty() const
	{
		return data_list.empty();
	}
};