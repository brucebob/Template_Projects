#pragma once

#include <vector>
#include <exception>
/*
*	SortedList
*	To Use this list on non-Primitives you need to over load the < > ==
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
	SortedList<T>(const std::vector<T>& vList)
	{
		for(std::vector<T>::const_iterator itor = vList.cbegin(); itor != vList.cend(); itor++)
		{
			add(*itor);
		}
	}
	const SortedList& operator=(const std::vector<T>& vList)
	{
		_list.clear();
		for(std::vector<T>::const_iterator itor = vList.cbegin(); itor != vList.cend(); itor++)
		{
			add(*itor);
		}
		return *this;
	}
	SortedList<T>(const SortedList& listIn)
	{
		_list = listIn._list;
	}
	const SortedList& operator=(const SortedList& listIn)
	{
		if(this != &listIn)
		{
			_list = listIn._list;
		}
		return *this;
	}
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
	void clear()
	{
		_list.clear();
	}
	void add(T && t)
	{
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
	void add(const T& t)
	{
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
	// binary search
	template<typename TT>
	const int positionOf(const TT& t)
	{
		if(_list.empty())
		{
			return -1;
		}
		else
		{
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
	template<typename TT>
	T* find(const TT& t)
	{
		if(_list.empty())
		{
			return nullptr;
		}
		else
		{
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
					return &_list[mid];
				}
			}
			return nullptr;
		}
	}
	void remove(const unsigned int spot)
	{
		if(spot < _list.size())
		{
			_list.erase(_list.begin() + spot);
		}
		else
		{
			throw std::out_of_range("Number inputed is out of range.");
		}
	}
	// should make this TT
	void remove(const T& t)
	{
		int spot = positionOf(t);
		if(spot != -1)
		{
			_list.erase(_list.begin() + spot);
		}
		else
		{
			throw std::exception("This element is not contained in the List.");
		}
	}
	const unsigned int size()
	{
		return _list.size();
	}
	bool isEmpty()
	{
		return _list.empty();
	}
};