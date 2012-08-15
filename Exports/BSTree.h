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
	Node<T>* parentOf(Node<T>* root, Node<T>* node)
	{
		if(root == nullptr)
		{
			return nullptr;
		}
		else
		{
			// The root is the parent
			if (root->left == node || root->right == node)
			{
				return root;
			}
			// Look in the left and the right side of the tree.
			if (node->d < root->d)
			{
				return parentOf(root->left, node);
			}
			else if (node->d > root->d)
			{
				return parentOf(root->right, node);
			}
		}
		return nullptr;
	}
	bool hasChild(Node<T>* node)
	{
		if(node->Left != nullptr || node->Right != nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool onlyLeftChild();
	bool onlyRightChild();

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
	T* findElement(const TT& t)
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
		return nullptr;
	}
	template<typename TT>
	const T* findElement(const TT& t) const
	{
		Node<T>* transPtr = tree;
		while(transPtr != nullptr)
		{
			if(transPtr->d < t)
			{
				transPtr = transPtr->Right;
			}
			else if(transPtr->d > t)
			{
				transPtr = transPtr->Left;
			}
			else
			{
				return &transPtr->d;
			}
		}
		return nullptr;
	}
	template<typename TT>
	bool removeElement(const TT& t)
	{
		if(FindElement(t) != nullptr)
		{
			Node<T>* element = findElement(t);
			Node<T>* parent = parentOf(element);
			// now i need to make sure they don't drop their leafs and things
		}
		return false;
	}
	Node<T>* maxElement()
	{

	}
	Node<T>* minElement()
	{

	}
	const Node<T>* maxElement() const
	{

	}
	const Node<T>* minElement() const
	{

	}
};


