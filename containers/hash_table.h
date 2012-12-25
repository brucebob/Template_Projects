#pragma once
#include "compare_function.h"

template<typename T, typename F = hash_func<T>>
class hash_table
{
private:
	struct cell
	{
		T data;
		struct cell * next;
	};

	unsigned int total_buckets;
	cell** table;
	
	cell** init(unsigned int hash_size)
	{
		cell** new_table = new cell*[hash_size];
		for(unsigned int x = 0; x < hash_size; x++)
		{
			new_table[x] = nullptr;
		}
		return new_table;
	}
	void clear_hash(cell** table_in, unsigned int hash_size)
	{
		for(unsigned int x = 0; x < total_buckets; x++)
		{
			cell* trans_ptr = table_in[x];
			while(trans_ptr != nullptr)
			{
				cell* delete_ptr = trans_ptr;
				trans_ptr = trans_ptr->next;
				delete delete_ptr;
			}
		}
		delete table_in;
	}
	cell* make_cell(const T& t)
	{
		cell* rtn_cell = new cell;
		if(rtn_cell == nullptr)
		{
			throw std::exception("unable to allocate memory");
		}
		rtn_cell->next = nullptr;
		rtn_cell->data = t;
		return rtn_cell;
	}
	cell* find_cell(cell* bucket, const T& t)
	{
		cell* trans_ptr = bucket;
		while(trans_ptr != nullptr && trans_ptr->data != t)
		{
			trans_ptr = trans_ptr->next;
		}
		return trans_ptr;
	}
public:
	hash_table(unsigned int hash_size) : total_buckets(hash_size) 
	{
		table = init(hash_size);
	}
	const T* find(const T& t)
	{
		int spot = F()(t, total_buckets);
		cell* found_cell = find_cell(table[spot] , t);
		return &found_cell->data;

	}
	void rehash(unsigned int hash_size)
	{
		cell** new_table = init(hash_size);


		for(unsigned int x = 0; x < total_buckets; x++)
		{
			for(cell* trans_ptr = table[x]; trans_ptr != nullptr; trans_ptr = trans_ptr->next)
			{
				int spot = F()(trans_ptr->data, hash_size);
				cell* new_cell = make_cell(trans_ptr->data);
				new_cell->next = new_table[spot];
				new_table[spot] = new_cell;
			}
		}

		clear_hash(table, total_buckets);
		total_buckets = hash_size;
		table = new_table;
	}
	void add(const T& t)
	{
		int spot = F()(t, total_buckets);
		cell* found_cell = find_cell(table[spot], t);

		if(found_cell == nullptr)
		{
			cell* new_front = make_cell(t);
			new_front->next = table[spot];
			table[spot] = new_front;
		}
		else
		{
			found_cell->data = t;
		}
	}
	void print_table()
	{
		std::cout << std::endl;
		for(unsigned int x = 0; x < total_buckets; x++)
		{
			cell* trans_ptr = table[x];
			while(trans_ptr != nullptr)
			{
				std::cout << trans_ptr->data << " ";
				trans_ptr = trans_ptr->next;
			}
			std::cout << "nullptr" << std::endl ;
		}
		std::cout << std::endl;
	}
	~hash_table()
	{
		for(unsigned int x = 0; x < total_buckets; x++)
		{
			cell* trans_ptr = table[x];
			while(trans_ptr != nullptr)
			{
				cell* delete_ptr = trans_ptr;
				trans_ptr = trans_ptr->next;
				delete delete_ptr;
			}
		}
		delete table;
	}
};