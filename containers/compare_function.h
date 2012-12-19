#pragma once

template<typename type>
struct pointer_compare_int
{
	int operator()(const type& a, const type& b)
	{
		if(*a < *b)
		{
			return -1;
		}
		else if(*a > *b)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
};
template<typename type>
struct compare_int
{
	int operator()(const type& a, const type& b)
	{
		if(a < b)
		{
			return -1;
		}
		else if(a > b)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
};
template<typename type>
struct pointer_compare_bool_less
{
	int operator()(const type& a, const type& b)
	{
		if(*a < *b)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
template<typename type>
struct pointer_compare_bool_greater
{
	int operator()(const type& a, const type& b)
	{
		if(*a > *b)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
template<typename type>
struct compare_bool_less
{
	int operator()(const type& a, const type& b)
	{
		if(a < b)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
template<typename type>
struct compare_bool_greater
{
	int operator()(const type& a, const type& b)
	{
		if(a < b)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};