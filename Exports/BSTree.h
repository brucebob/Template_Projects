#pragma once

template <typename T>
class BSTree
{
private:
	template <typename T>
	struct Node
	{
		T d;
		struct Node<T>* Left;
		struct Node<T>* Right;
	};
	Node<T>* Tree;
public:
	BSTree<T>()
	{
		Tree = nullptr;
	}
	BSTree<T>(const BSTree<T>& TreeIn)
	{

	}
	const BSTree<T>& operator =(const BSTree<T>& TreeIn)
	{

	}
	void addElement(const T& elementIn)
	{

	}
	void addElement(T && elementIn)
	{

	}
	template<typename TT>
	const T& FindElement(const TT& t)
	{

	}
};

/*
template <typename T>
class BSTree
{
private:
	template <typename T>
	struct Node
	{
		T d;
		struct Node* Left;
		struct Node* Right;
	};
	Node<T>* Tree;
	Node<T>* MakeNode(const T& t)
	{
		Node<T>* out = new Node<T>;
		if(out == nullptr)
		{
			throw std::bad_alloc("Was unable to gather space for TreeNode");
		}
		out->d = t;
		out->Left = out->Right = nullptr;
		return out;
	}
	int compare(const std::string& b, const std::string& t)
	{
		return b.compare(t);
	}
	template <typename T>
	int compare(const T& b, const T& t)
	{
		if(b < t)
		{
			return 1;
		}
		else if(b > t)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
	virtual void addf(Node<T>** TreeIn, const T& t)
	{
		if(*TreeIn == nullptr)
		{
			*TreeIn = MakeNode(t);
		}
		else if(compare((*TreeIn)->d, t) == 1)
		{
			if((*TreeIn)->Right != nullptr)
			{
				addf(&(*TreeIn)->Right, t);
			}
			else
			{
				(*TreeIn)->Right = MakeNode(t);
			}
		}
		else 
		{
			if((*TreeIn)->Left != nullptr)
			{
				addf(&(*TreeIn)->Left, t);
			}
			else
			{
				(*TreeIn)->Left = MakeNode(t);
			}
		}
	}
	void deleteForward(Node<T>** TreeIn)
	{
		if(*TreeIn != nullptr)
		{
			if((*TreeIn)->Left != nullptr)
			{
				deleteForward(&(*TreeIn)->Left);
			}
			if((*TreeIn)->Right != nullptr)
			{
				deleteForward(&(*TreeIn)->Right);
			}
			delete *TreeIn;
		}
	}
	const T& MaxForward(Node<T>* TreeIn) const
	{
		if(TreeIn->Left == nullptr)
		{
			return TreeIn->d;
		}
		else
		{
			return MaxForward(TreeIn->Left);
		}
	}
	const T& MinForward(Node<T>* TreeIn) const
	{
		if(TreeIn->Right == nullptr)
		{
			return TreeIn->d;
		}
		else
		{
			return MinForward(TreeIn->Right);
		}
	}
	bool FindForward(Node<T>* TreeIn, const T& target)
	{
		if(TreeIn != nullptr)
		{
			if(compare(TreeIn->d, target) == 1)
			{
				return FindForward(TreeIn->Right, target);
			}
			else if(compare(TreeIn->d, target) == -1)
			{
				return FindForward(TreeIn->Left, target);
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
public:
	
	BSTree()
	{
		Tree = nullptr;
	}
	void add(T t)
	{
		addf(&Tree, t);	
	}
	bool IsEmpty()
	{
		if(Tree == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	const T& MaxElement() const
	{
		if(Tree != nullptr)
		{
			return MaxForward(Tree);
		}
		else
		{
			throw("No Elements in the tree");
		}
	}
	const T& MinElement() const
	{
		if(Tree != nullptr)
		{
			return MinForward(Tree);
		}
		else
		{
			throw("No Elements in the tree");
		}
	}
	bool FindElement(const T& t)
	{
		if(Tree != nullptr)
		{
			return FindForward(Tree, t);
		}
		else
		{
			throw("No Elements in the tree");
		}
	}
	~BSTree()
	{
		if(Tree != nullptr)
		{
			deleteForward(&Tree);
		}
	}
};
*/