#pragma once

#include <list>
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
	Node<T>* tree;
	Node<T>* makeNode(const T& t)
	{
		Node<T>* newNode = new Node<T>;
		newNode->d = t;
		newNode->Right = nullptr;
		newNode->Left = nullptr;
		return newNode;
	}
public:
	~BSTree<T>()
	{
		if(tree != nullptr)
		{
			std::list<Node<T>*> stack;
			stack.push_back(tree);
			while(!stack.empty())
			{
				Node<T>* transPtr = stack.front();
				if(transPtr->Left != nullptr)
				{
					stack.push_back(transPtr->Left);
				}
				if(transPtr->Right != nullptr)
				{
					stack.push_back(transPtr->Right);
				}
				delete stack.front();
				stack.pop_front();
			}
		}
	}
	BSTree<T>()
	{
		tree = nullptr;
	}
	BSTree<T>(const BSTree<T>& TreeIn)
	{
		// need a copy of the bst struct with a BFS
	}
	const BSTree<T>& operator =(const BSTree<T>& TreeIn)
	{
		// need a deep copy of the pointers
	}
	// needs to be copied into both adds same code but different appected par
	void add(const T& elementIn)
	{
		if(tree == nullptr)
		{
			tree = makeNode(elementIn);
		}
		else
		{
			Node<T>* transPtr = tree;
			while(transPtr != nullptr)
			{
				if(transPtr->d > elementIn)
				{
					if(transPtr->Left == nullptr)
					{
						transPtr->Left = makeNode(elementIn);
						return;
					}
					transPtr = transPtr->Left;
				}
				else
				{
					if(transPtr->Right == nullptr)
					{
						transPtr->Right = makeNode(elementIn);
						return;
					}
					transPtr = transPtr->Right;
				}
			}
		}
	}
	void add(T && elementIn)
	{
		if(tree == nullptr)
		{
			tree = newNode(elementIn);
		}
		else
		{
			Node<T>* transPtr = tree;
			while(transPtr != nullptr)
			{
				if(transPtr->d > elementIn)
				{
					if(transPtr->Left == nullptr)
					{
						transPtr->Left = newNode(elementIn);
						return;
					}
					transPtr = transPtr->Left;
				}
				else
				{
					if(transPtr->Right == nullptr)
					{
						transPtr->Right = newNode(elementIn);
						return;
					}
					transPtr = transPtr->Right;
				}
			}
		}
	}
	template<typename TT>
	T* FindElement(const TT& t)
	{
		if(tree != nullptr)
		{
			Node<T>* transPtr = tree;
			while(transPtr != nullptr)
			{
				if(transPtr->d > t)
				{
					transPtr = transPtr->Left;
				}
				else if(transPtr->d < t)
				{
					transPtr = transPtr->Right;
				}
				else
				{
					return &transPtr->d;
				}
			}
		}
		return nullptr;
	}
	template<typename TT>
	const T* FindElement(const TT& t) const
	{
		if(tree != nullptr)
		{

		}
	}
};


