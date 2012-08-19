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
private:
	Node<T>* makeNode(const T& t)
	{
		Node<T>* newNode = new Node<T>;
		if(newNode != nullptr)
		{
			newNode->d = t;
			newNode->Right = nullptr;
			newNode->Left = nullptr;
			return newNode;
		}
		else
		{
			throw std::bad_alloc("BSTree: ran out of memory");
		}
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
			if (root->Left == node || root->Right == node)
			{
				return root;
			}
			// Look in the left and the right side of the tree.
			if (node->d < root->d)
			{
				return parentOf(root->Left, node);
			}
			else if (node->d > root->d)
			{
				return parentOf(root->Right, node);
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
	bool onlyLeftChild(Node<T>* node)
	{
		if(node->Left != nullptr && node->Right == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool onlyRightChild(Node<T>* node)
	{
		if(node->Right != nullptr && node->Left == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	Node<T>* maxLeaf(Node<T>* node) const
	{
		while(node->Right != nullptr)
		{
			node = node->Right;
		}
		return node;
	}
	Node<T>* minLeaf(Node<T>* node) const
	{
		while(node->Left != nullptr)
		{
			node = node->Left;
		}
		return node;
	}
	Node<T>* findNode(Node<T>* root, T t) const
	{
		Node<T>* transPtr = root;
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
				return transPtr;
			}	
		}
		return nullptr;
	}
	Node<T>* copyTree(Node<T>* root)
	{
		if(root != nullptr)
		{
			Node<T>* newRoot = nullptr;
			std::list<Node<T>*> stack;
			
			stack.push_back(root);
			while(!stack.empty())
			{
				if(stack.front()->Left != nullptr)
				{
					stack.push_back(stack.front()->Left);
				}
				if(stack.front()->Right != nullptr)
				{
					stack.push_back(stack.front()->Right);
				}
				newRoot = addElement(newRoot, stack.front()->d);
				stack.pop_front();
			}

			return newRoot;
		}
		return nullptr;
	}
	Node<T>* addElement(Node<T>* root, const T& element)
	{
		if(root == nullptr)
		{
			return makeNode(element);
		}
		else
		{
			Node<T>* transPtr = root;
			while(transPtr != nullptr)
			{
				if(transPtr->d > element)
				{
					if(transPtr->Left == nullptr)
					{
						transPtr->Left = makeNode(element);
						return root;
					}
					transPtr = transPtr->Left;
				}
				else
				{
					if(transPtr->Right == nullptr)
					{
						transPtr->Right = makeNode(element);
						return root;
					}
					transPtr = transPtr->Right;
				}
			}
		}
		return root;
	}
public:
	~BSTree<T>()
	{
		clear();
	}
	BSTree<T>()
	{
		tree = nullptr;
	}
	BSTree<T>(const BSTree<T>& TreeIn)
	{
		tree = copyTree(TreeIn.tree);
	}
	const BSTree<T>& operator =(const BSTree<T>& TreeIn)
	{
		// need a deep copy of the pointers and nodes
		if(this != &TreeIn)
		{
			clear();
			tree = copyTree(TreeIn.tree);
		}
		return *this;
	}
	// needs to be copied into both adds same code but different appected par
	void add(const T& elementIn)
	{
		tree = addElement(tree, elementIn);
	}
	void add(T && elementIn)
	{
		tree = addElement(tree, elementIn);
	}
	template<typename TT>
	T* findElement(const TT& t)
	{
		if(tree != nullptr)
		{
			return &findNode(tree, t)->d; 
		}
		else
		{
			return nullptr;
		}
	}
	template<typename TT>
	const T* findElement(const TT& t) const
	{
		if(tree != nullptr)
		{
			return &findNode(tree, t)->d; 
		}
		else
		{
			return nullptr;
		}
	}
	template<typename TT>
	bool removeElement(const TT& t)
	{
		Node<T>* element = findNode(tree,t);
		if(element != nullptr)
		{
			Node<T>* parent = parentOf(tree, element);
			// checks to see if it's a leaf node
			if(!hasChild(element))
			{
				// it's a leaf node but not the root
				if(parent != nullptr)
				{
					if(parent->Left == element)
					{
						parent->Left = nullptr;
					}
					else
					{
						parent->Right = nullptr;
					}
					delete element;
				}
				else // it's the root node with no children
				{
					delete element;
					tree = nullptr;
				}
			}
			// it's a edge node
			else
			{
				// only has one left child 
				if(onlyLeftChild(element))
				{
					if(parent != nullptr)
					{
						parent->Left = element->Left;
						if(parent->Left == element)
						{
							parent->Left = element->Left;
						}
						else
						{
							parent->Right = element->Left;
						}
					}
					else
					{
						tree = element->Left;
					}
					delete element;
				}
				// only has one right child
				else if(onlyRightChild(element))
				{
					if(parent != nullptr)
					{			
						if(parent->Left == element)
						{
							parent->Left = element->Right;
						}
						else
						{
							parent->Right = element->Right;
						}
					}
					else
					{
						tree = element->Right;
					}
					delete element;
				}
				else
				{
					// has both left and right
					// right's left goes on left's max right
					if(element->Left != nullptr)
					{
						maxLeaf(element->Left)->Right = element->Right->Left;
					}
					else
					{
						element->Left = element->Right->Left;
					}
					// left goes on the right's min left
					element->Right->Left = element->Left;
					if(parent != nullptr)
					{
						if(parent->Left == element)
						{
							parent->Left = element->Right;
						}
						else
						{
							parent->Right = element->Right;
						}
						delete element;
					}
					else
					{
						// it's the root
						tree = element->Right;
						delete element;
					}
				}
			}
			return true;
		}
		return false;
	}
	T* maxElement()
	{
		if(tree == nullptr)
		{
			return nullptr;
		}
		else
		{
			return &maxLeaf(tree)->d;
		}
	}
	T* minElement()
	{
		if(tree == nullptr)
		{
			return nullptr;
		}
		else
		{
			return &minLeaf(tree)->d;
		}
	}
	const T* maxElement() const
	{
		if(tree == nullptr)
		{
			return nullptr;
		}
		else
		{
			return &maxLeaf(tree)->d;
		}
	}
	const T* minElement() const
	{
		if(tree == nullptr)
		{
			return nullptr;
		}
		else
		{
			return &minLeaf(tree)->d;
		}
	}
	bool isEmpty() const 
	{
		return tree == nullptr;
	}
	void clear()
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
			tree = nullptr;
		}
	}

	// going to have bi direction type iterators with a vector of *

	// in order is only going to be a forward iterator

	// for this to be not all the element i have to keep a list of the list till the min node and as i
	// ++ throught make sure they don't have a right.
	/*
	class inOrderIterator
	{
	private:
		std::vector<Node<T>*> ioiList;
		unsigned int cSpot;
	public:
		
		void operator++(int)
		{
			cSpot++;
		}
		T& operator*()
		{
			return ioiList[cSpot];
		}
		T* operator->() const
		{
			return &ioiList[cSpot];
		}
		inOrderIterator(
	};*/
};