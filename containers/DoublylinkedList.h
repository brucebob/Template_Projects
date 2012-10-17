#pragma once

template<typename T>
class DoublyLinkedList
{
private:
	template<typename T>
	struct Node
	{
		T data;
		Node<T>* next;
		Node<T>* before;
	};
	Node<T>* head;
	Node<T>* tail;
	unsigned int list_size;
	Node<T>* make_node(const T& t)
	{
		Node<T>* rtn_ptr = new Node<T>;
		if(rtn_ptr == nullptr)
		{
			throw std::exception("DoublyLinkedList: unable to allocate memory");
		}
		rtn_ptr->next = nullptr;
		rtn_ptr->before = nullptr;
		rtn_ptr->data = t;
		return rtn_ptr;
	}
	void init()
	{
		tail = nullptr;
		head = nullptr;
		list_size = 0;
	}
public:
	class iterator
	{
	private:
		Node<T>* current_pos;
	public:
		iterator()
		{
			current_pos = nullptr;
		}
		iterator(Node<T>* t)
		{
			current_pos = t;
		}
		iterator(const iterator& t)
		{
			current_pos = t.current_pos;
		}
		iterator& operator=(const iterator& t)
		{
			if(this != &t)
			{
				current_pos = t.current_pos;
			}
			return *this;
		}
		T& operator*() const
		{
			if(current_pos == nullptr)
			{
				throw std::exception("");
			}
			return current_pos->data;
		}
		T* operator->() const
		{
			if(current_pos == nullptr)
			{
				throw std::exception("");
			}
			return current_pos->data;
		}
		void operator++(int)
		{
			if(current_pos == nullptr)
			{
				throw std::exception("");
			}
			current_pos = current_pos->next;
		}
		void operator--(int)
		{
			if(current_pos == nullptr)
			{
				throw std::exception("");
			}
			current_pos = current_pos->before;
		}
		iterator operator-(unsigned int off_set)
		{
			Node<T>* trans_ptr = current_pos;
			while(off_set != 0)
			{
				if(trans_ptr == nullptr)
				{
					throw std::exception("iterator: out of range:");
				}
				trans_ptr = trans_ptr->before;
				off_set--;
			}
			return iterator(trans_ptr);
		}
		iterator operator+(unsigned int off_set)
		{
			Node<T>* trans_ptr = current_pos;
			while(off_set != 0)
			{
				if(trans_ptr == nullptr)
				{
					throw std::exception("iterator: out of range:");
				}
				trans_ptr = trans_ptr->next;
				off_set--;
			}
			return iterator(trans_ptr);
		}
		void operator!=(const iterator& t) const
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
	};
	DoublyLinkedList<T>()
	{
		init();
	}
	DoublyLinkedList<T>(const DoublyLinkedList& t)
	{
		init();
		Node<T>* trans_ptr = t.head;
		while(trans_ptr != nullptr)
		{
			push_back(trans_ptr->data);
			trans_ptr = trans_ptr->next;
		}
	}
	const DoublyLinkedList<T>& operator=(const DoublyLinkedList& t)
	{
		if(this != &t)
		{
			clear();
			init();
			Node<T>* trans_ptr = t.head;
			while(trans_ptr != nullptr)
			{
				push_back(trans_ptr->data);
				trans_ptr = trans_ptr->next;
			}
		}
		return *this;
	}
	~DoublyLinkedList<T>()
	{
		clear();
	}
	void pop_back()
	{
		if(empty())
		{
			throw std::exception("DoublyLinkedList: No elements");
		}
		Node<T>* dlt_node = tail;
		if(dlt_node->before != nullptr)
		{
			tail = tail->before;
			tail->next = nullptr;
		}
		else
		{
			tail = head = nullptr;
		}
		list_size--;
		delete dlt_node;
	}
	void pop_front()
	{
		if(empty())
		{
			throw std::exception("DoublyLinkedList: No elements");
		}
		Node<T>* dlt_node = head;

		if(dlt_node->next != nullptr)
		{
			head = head->next;
			head->before = nullptr;
		}
		else
		{
			head = tail = nullptr;
		}
		list_size--;
		delete dlt_node;
	}
	T& front() const
	{
		return head->data;
	}
	T& back() const
	{
		return tail->data;
	}
	iterator begin()
	{
		return iterator(head);
	}
	iterator end()
	{
		return iterator(tail);
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
			tail->next->before = tail;
			tail = tail->next;
		}
		list_size++;
	}
	void push_front(const T& t)
	{
		Node<T>* new_head = make_node(t);
		if(empty())
		{
			head = tail = new_head;
		}
		else
		{
			new_head->next = head;
			head->before = new_head;
			head = new_head;
		}
		list_size++;
	}
	void clear()
	{
		while(head != nullptr)
		{
			Node<T>* dlt_node = head;
			head = head->next;
			delete dlt_node;
		}
		head = nullptr;
		tail = nullptr;
		list_size = 0;
	}
	bool empty() const
	{
		return head == nullptr ? true : false;
	}
	unsigned int size() const
	{
		return list_size;
	}
	template<typename TT>
	iterator find(const TT& t)
	{
		Node<T>* trans_ptr = head;
		while(trans_ptr != nullptr)
		{
			if(trans_ptr->data == t)
			{
				return iterator(trans_ptr);
			}
			trans_ptr = trans_ptr->next;
		}
		return iterator(nullptr);
	}
	template<typename TT>
	iterator rfind(const TT& t)
	{
		Node<T>* trans_ptr = head;
		while(trans_ptr != nullptr)
		{
			if(trans_ptr->data == t)
			{
				return iterator(trans_ptr);
			}
			trans_ptr = trans_ptr->before;
		}
		return iterator(nullptr);
	}
};