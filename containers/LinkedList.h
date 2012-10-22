#pragma once
#include <exception>
/*
		#TODOs
		need a const iterator
		need to do fault test to test exceptions
		need to add U ref for push back
		need a insert function at a iterator
*/

/*
*			LinkList
*	To be able to use remove and find on complex classes it must have a overloaded ==
*	Also for complex element you need a overloaded copy constructor
*/
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
	// this inner class help the linklist transverse through it nodes and keeps the user away from messing up the list.
	class forward_iterator
	{
	private:
		// holds a pointer to a point between {head:tail}
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
			if(current_pos == t.current_pos)
			{
				return false;
			}
			else
			{
				return true;
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
		// this is user for the find function so if you try to deref the iterator 
		// it doesn't blow up the program
		bool valid() const
		{
			return current_pos == nullptr ? false : true;
		}
	};
	// basic constructor sets values to 0 and points to nullptr
	LinkedList<T>()
	{
		init();
	}
	// a deep copy constructor
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
	// a deep copy constructor clears the old data before coping the incoming linklist
	const LinkedList<T>& operator=(const LinkedList& t)
	{
		if(this != &t)
		{
			clear();
			init();
			Node<T>* transptr = t.head;
			while(transptr != nullptr)
			{
				push_back(transptr->data);
				transptr = transptr->next;
			}
		}
		return *this;
	}
	// take a iterator and makes a linklist to the end of the iterator
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
	// once delete or the class falls out of scope it calls clear and remove all the nodes
	~LinkedList<T>()
	{
		clear();
	}
	// removes the front most element from the linklist
	// throw if the linklist is empty
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
	// return a pointer to the front of the element of linklist
	forward_iterator begin()
	{
		return forward_iterator(head);
	}
	// return a pointer to the last element in the linklist
	forward_iterator end()
	{
		return forward_iterator(tail->next);
	}
	// returns the front element of the linklist
	// throw if the linklist is empty
	T& front() const
	{
		if(head == nullptr)
		{
			throw std::exception("LinkedList: out of range no elements");
		}
		return head->data;
	}
	// returns the element at the back of the linklist
	// throw if the linklist is empty
	T& back() const
	{
		if(tail == nullptr)
		{
			throw std::exception("LinkedList: out of range no elements");
		}
		return tail->data;
	}
	// adds a element to the back of the linklist
	// throws if the element is unable to be allocated
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
	// adds a element to the front of the list
	// throws if the element is unable to be allocated
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
	// removes all Nodes in the linklist and sets the size back to 0
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
	// return a boolean that figures out if the linklist is empty
	bool empty() const
	{
		return !list_size;
	}
	// return a unsigned int of the size of the linklist
	unsigned int size() const
	{
		return list_size;
	}
	// return a point of where the element is if element is not found it's return a null inner pointer 
	// must use valid on the iterator to check.
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
			trans_ptr = trans_ptr->next;
		}
		return forward_iterator(nullptr);
	}
	// return a boolean of if it was found
	// if false the item you inputed is not in the linklist
	template<typename TT>
	bool remove(const TT t)
	{
		if(head != nullptr && head->data == t)
		{
			Node<T>* dlt_ptr = head;
			if(head->next == nullptr)
			{
				tail = head = nullptr;
			}
			else
			{
				head = head->next;
			}
			list_size--;
			delete dlt_ptr;
			return true;
		}
		else
		{
			Node<T>* trans_ptr = head;
			while(trans_ptr->next != nullptr)
			{
				if(trans_ptr->next->data == t)
				{
					Node<T>* dlt_ptr = trans_ptr->next;
					trans_ptr->next = trans_ptr->next->next;
					list_size--;
					delete dlt_ptr;
					return true;
				}
			}
		}
		return false;
	}
};