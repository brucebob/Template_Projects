#pragma once
// to do for the list is to add a pointer to the back when adding elements so i can have over more then
// 10000 elements in the list or remove the recursion part of the add function.
template <typename T>
class List
{
private:
	template <typename T>
	struct data
	{
		T s;
		struct data<T>* next;
	};
private:
	data<T>* MakeNode(T t)
	{
		data<T>* temp = new data<T>;
		if(temp == nullptr)	throw std::bad_alloc("Was unable to gather space for TreeNode");

		temp->s = t;
		temp->next = nullptr;
		return temp;
	}
	data<T>* list;
protected:	
	data<T>* Copy(data<T>* ListIn)
	{
		data<T>* newList = nullptr;
		data<T>* transptr = ListIn;
		while(transptr != nullptr)
		{
			pushf(&newList, MakeNode(transptr->s));
			transptr = transptr->next;
		}
		return newList;
	}
	void SetList(data<T>* listIn)
	{
		list = listIn;
	}
	data<T>* GetList() const
	{
		return list;
	}
	virtual void pushf(data<T>** l, data<T>* t)
	{
		if(*l == nullptr)
		{
			*l = t;
		}
		else
		{
			if((*l)->next != nullptr)
			{
				pushf(&(*l)->next, t);
			}
			else
			{
				(*l)->next = t;
			}
		}
	}
public:
	List()
	{
		list = nullptr;
	}
	List<T>& operator=(const List<T>& ListIn)
	{
		if(this != &ListIn)
		{
			clear();
			// have to make sure the list is null before i copy the new list;
			
			list = Copy(ListIn.list);
		}
		return *this;
	}
	// a deep copy of the data struct
	List<T>(const List<T>& ListIn)
	{
		list = Copy(ListIn.list);
	}
	void push(T t)
	{
		pushf(&list, MakeNode(t));
	}
	const T& peek()
	{
		if(!isEmpty())
		{
			return list->s;
		}
		else
		{
			throw std::exception("No Nodes in the Linklist");
		}
	}
	const T pop()
	{
		if(list != nullptr)
		{
			data<T>* tempNode = list;
			T temp = tempNode->s;
			list = list->next;

			delete tempNode;
			return temp;
		}
		else
		{
			throw std::exception("No Nodes in the Linklist");
		}
	}
	bool isEmpty()
	{
		if(list == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void clear()
	{
		while(list != nullptr)
		{
			data<T>* dltptr = list;
			list = list->next;
			delete dltptr;
		}
	}
	virtual ~List()
	{
		if(list != nullptr) clear();
	}
	data<T>** front()
	{
		return &list;
	}
	data<T>* const_front() const 
	{
		return list;
	}
public:
	class ListIterator
	{
	private:
		data<T>** w;
	protected:
		data<T>** getdata()
		{
			return w;
		}
	public:
		ListIterator operator=(data<T>* Front)
		{
			w = &Front;
		}
		ListIterator(data<T>** Front)
		{
			w =	Front;
		}
		ListIterator()
		{
			w = nullptr;
		}
		T& operator*()
		{
			return (*w)->s;
		}
		T* operator->() const
		{
			return &(*w)->s;
		}
		void operator++(int)
		{
			w = &(*w)->next;
		}
		bool operator!=(struct data<T>*)
		{
			if(*w == nullptr)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	};
	class Const_ListIterator
	{
	private:
		data<T>* w;
	public:
		Const_ListIterator operator=(data<T>* Front)
		{
			w = Front;
		}
		Const_ListIterator(data<T>* Front)
		{
			w = Front;
		}
		Const_ListIterator()
		{
			w = nullptr;
		}
		const T& operator*() const
		{
			return w->s;
		}
		const T* operator->() const
		{
			return &w->s;
		}
		void operator++(int)
		{
			w = w->next;
		}
		bool operator!=(data<T>*) const
		{
			if(w == nullptr)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	};
};
/*			USING THE SORTED LIST CLASS WITH NON-PRIMITIVES
*	for using this container with non-primitives
*	the class must contain a friend functions of
*	friend bool operator<(const T& T1, const T& T2);
*	the same goes for the other comparing operators
*/
template <typename T>
class SortedList: public List<T>
{
protected:
	template<typename T>
	int Compare(const T& T1, const T& T2)
	{
		if(T1 > T2)
		{
			return -1;
		}
		else if(T1 < T2)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	virtual void pushf(struct data<T>** l, struct data<T>* t)
	{
		// need a compare type algorithm 
		if(*l == nullptr || Compare((*l)->s, t->s) == -1)
		{
			t->next = *l;
			*l = t;
		}
		else
		{
			if((*l)->next != nullptr && Compare((*l)->next->s, t->s) == 1)
			{
				pushf(&(*l)->next, t);
			}
			else
			{
				t->next = (*l)->next;
				(*l)->next = t;
			}
		}
	}
public:
	SortedList<T>():List<T>()
	{

	}
	SortedList<T>(const SortedList<T>& s)
	{
		SetList(Copy(s.GetList()));
	}
	SortedList<T>& operator=(const SortedList<T>& s)
	{
		if(this != &s)
		{
			clear();
			SetList(Copy(s.GetList()) );
		}
		return *this;
	}
	SortedList<T>(const List<T>& s): List<T>()
	{
		for(List<T>::Const_ListIterator itor = s.const_front(); itor != nullptr; itor++)
		{
			push(*itor);
		}
	}
	SortedList<T>& operator=(const List<T>& s)
	{
		// return CopyList(s
		clear();
		for(List<T>::Const_ListIterator itor = s.const_front(); itor != nullptr; itor++)
		{
			push(*itor);
		}
		return *this;
	}
};