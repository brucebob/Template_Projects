#pragma once
#include <exception>

template<typename T>
class LinkedList
{
private:
	template<typename T>
	struct Node
	{
		T data;
		Node<T>* next;
	};
	Node<T>* make_node(const T& t)
	{
		Node<T>* rtn_ptr = new Node<T>;
		if(rtn_ptr == nullptr)
		{
			throw std::exception("LinkedList: unable to allocate memory");
		}
		rtn_ptr->data = t;
		rtn_ptr->next = nullptr;
		return rtn_ptr;
	}
	void init()
	{
		head = nullptr;
		tail = nullptr;
		list_size = 0;
	}
	unsigned int list_size;
	Node<T>* head;
	Node<T>* tail;
public:
	class forward_iterator
	{
	private:
		Node<T>* current_pos;
	public:
		forward_iterator()
		{
			current_pos = nullptr;
		}
		forward_iterator(Node<T>* t)
		{
			current_pos = t;
		}
		forward_iterator(const forward_iterator& t)
		{
			current_pos = t.current_pos;
		}
		const forward_iterator& operator=(const forward_iterator& t)
		{
			if(this != &t)
			{
				current_pos = t.current_pos;
			}
			return *this;
		}
		void operator++(int)
		{
			if(current_pos == nullptr)
			{
				throw std::exception("iterator: out of range error");
			}
			current_pos = current_pos->next;
		}
		bool operator!=(const forward_iterator& t) const
		{
			if(current_pos != nullptr)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		forward_iterator operator+(unsigned int n)
		{
			Node<T>* trans_ptr = current_pos;
			while(n != 0)
			{
				if(trans_ptr == nullptr)
				{
					throw std::exception("iterator: out of range:");
				}
				trans_ptr = trans_ptr->next;
				n--;
			}
			return forward_iterator(trans_ptr);
		}
		T* operator->() const
		{
			if(current_pos == nullptr)
			{
				throw std::exception("iterator: out of range");
			}
			return &current_pos->next; 
		}
		T& operator*() const
		{
			if(current_pos == nullptr)
			{
				throw std::exception("iterator: out of range");
			}
			return current_pos->data;
		}
		bool valid() const
		{
			return current_pos == nullptr ? false : true;
		}
	};
	LinkedList<T>()
	{
		init();
	}
	LinkedList<T>(const LinkedList& t)
	{
		init();
		Node<T>* transptr = t.head;
		while(transptr != nullptr)
		{
			push_back(transptr->data);
			transptr = transptr->next;
		}
	}
	const LinkedList<T>& operator=(const LinkedList& t)
	{
		if(this != &t)
		{
			clear();
			init();
			Node<T>* transptr = t.head;
			while(transptr != nullptr)
			{
				push_back(transptr.data);
				transptr = transptr->next;
			}
		}
		return *this;
	}
	LinkedList<T>(const forward_iterator& t)
	{
		init();
		forward_iterator trans_itor = t;
		while(trans_itor.valid())
		{
			push_back(*trans_itor);
			trans_itor++;
		}
	}
	~LinkedList<T>()
	{
		clear();
	}
	void pop_front()
	{
		if(head == nullptr)
		{
			throw std::exception("LinkedList: no elements in container");
		}
		
		Node<T>* delptr = head;
		head = head->next;
		if(list_size == 1)
		{
			tail = nullptr;
		}
		list_size--;
		delete delptr;
	}
	forward_iterator begin()
	{
		return forward_iterator(head);
	}
	forward_iterator end()
	{
		return forward_iterator(tail);
	}
	T& front() const
	{
		if(head == nullptr)
		{
			throw std::exception("LinkedList: out of range no elements");
		}
		return head->data;
	}
	T& back() const
	{
		if(tail == nullptr)
		{
			throw std::exception("LinkedList: out of range no elements");
		}
		return tail->data;
	}
	void push_back(const T& t)
	{
		if(empty())
		{
			head = tail = make_node(t);
		}
		else
		{
			tail->next = make_node(t);
			tail = tail->next;
		}
		list_size++;
	}
	void push_front(const T& t)
	{
		if(empty())
		{
			head = tail = make_node(t);
		}
		else
		{
			Node<T>* new_head = make_node(t);
			new_head->next = head;
			head = new_head;
		}
		list_size++;
	}
	void clear()
	{
		while(head != nullptr)
		{
			Node<T>* delptr = head;
			head = head->next;
			delete delptr;
		}
		list_size = 0;
		head = nullptr;
		tail = nullptr;
	}
	bool empty() const
	{
		return !list_size;
	}
	unsigned int size() const
	{
		return list_size;
	}
	template<typename TT>
	forward_iterator find(const TT& t)
	{
		Node<T>* trans_ptr = head;

		while(trans_ptr != nullptr)
		{
			if(trans_ptr->data == t)
			{
				return forward_iterator(trans_ptr);
			}
		}
		return forward_iterator(nullptr);
	}
};