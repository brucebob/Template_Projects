#pragma once
#include <list>


/*
*
*		BSTree is a simple binary search tree
*		for complex element overloads of < > are needed
*
*/


template <typename T>
class BSTree
{
private:
	// the stuct of tree
	template <typename T>
	struct Node
	{
		T d;
		struct Node<T>* Left;
		struct Node<T>* Right;
	};
	Node<T>* tree;
	unsigned int totalElements;
private:
	// makes the node for the tree
	// checks to see if it runs out of memmory and throws a bad_alloc
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
	// takes in two pointers one to the root and the one to the node
	// finds the parent of node and returns it
	// returns nullptr if it's the root node
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
	// returns true if either left or right is not nullptr
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
	// return true if only the left child is not nullptr
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
	// return true if only the right child is not nullptr
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
	// returns the node at the far node right
	Node<T>* maxLeaf(Node<T>* node) const
	{
		while(node->Right != nullptr)
		{
			node = node->Right;
		}
		return node;
	}
	// returns the node on the far left
	Node<T>* minLeaf(Node<T>* node) const
	{
		while(node->Left != nullptr)
		{
			node = node->Left;
		}
		return node;
	}
	// returns the node based on the binary search tree property
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
	// takes in the root and makes a complete copy of the tree struct
	Node<T>* copyTree(Node<T>* root)
	{
		if(root != nullptr)
		{
			Node<T>* newRoot = nullptr;
			// makes a BFS to copy the nodes
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
	// adds a new element to a empty child based of the binary search property
	Node<T>* addElement(Node<T>* root, const T& element)
	{
		totalElements++;
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
	// calls clear at the end of the scope of this class or is deleted
	~BSTree<T>()
	{
		clear();
	}
	// sets the tree to nullptr
	BSTree<T>()
	{
		totalElements = 0;
		tree = nullptr;
	}
	// copy constructor
	BSTree<T>(const BSTree<T>& TreeIn)
	{
		totalElements = TreeIn.totalElements;
		tree = copyTree(TreeIn.tree);
	}
	// deep copy constructor
	const BSTree<T>& operator =(const BSTree<T>& TreeIn)
	{
		// need a deep copy of the pointers and nodes
		if(this != &TreeIn)
		{
			clear();
			totalElements = TreeIn.totalElements;
			tree = copyTree(TreeIn.tree);
		}
		return *this;
	}
	// adds a element to the tree
	void add(const T& elementIn)
	{
		tree = addElement(tree, elementIn);
	}
	// adds a element to the tree
	void add(T && elementIn)
	{
		tree = addElement(tree, elementIn);
	}
	// find a element in the tree and uses the overload < > if the class has one
	// or uses the default T
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
	// find a element in the tree and uses the overload < > if the class has one
	// or uses the default T
	// and returns the T or nullptr
	// is const so it's immutable
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
	// removes a element in the tree and uses the overload < > if the class has one
	// or uses the default T
	// return true that it was delete or false that it was not found 
	template<typename TT>
	bool removeElement(const TT& t)
	{
		Node<T>* element = findNode(tree,t);
		if(element != nullptr)
		{
			Node<T>* parent = parentOf(tree, element);
			// checks to see if it's a leaf node
			totalElements--;
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
	// return the max element in the tree mutable
	T* maxElement()
	{
		if(isEmpty())
		{
			return nullptr;
		}
		else
		{
			return &maxLeaf(tree)->d;
		}
	}
	// returns the min element in the tree mutable
	T* minElement()
	{
		if(isEmpty())
		{
			return nullptr;
		}
		else
		{
			return &minLeaf(tree)->d;
		}
	}
	// returns the max element and it's nonmutable
	const T* maxElement() const
	{
		if(isEmpty())
		{
			return nullptr;
		}
		else
		{
			return &maxLeaf(tree)->d;
		}
	}
	// returns the min element and it's nonmutable
	const T* minElement() const
	{
		if(isEmpty())
		{
			return nullptr;
		}
		else
		{
			return &minLeaf(tree)->d;
		}
	}
	// return if the tree pointer is nullptr since it means it's empty
	bool isEmpty() const 
	{
		return tree == nullptr;
	}
	// delete the tree and sets it back to nullptr
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
		}
		tree = nullptr;
	}
	const unsigned int size() const
	{
		return totalElements;
	}

	// going to have bi direction type iterators with a vector of *

	// in order is only going to be a forward iterator

	// for this to be not all the element i have to keep a list of the list till the min node and as i
	// ++ throught make sure they don't have a right.
	/*
	class inOrderIterator
	{
	private:
		std::list<Node<T>*> ioiList;
	public:
		void operator++(int)
		{
			cSpot++;
		}
		T& operator*()
		{
			return ioiList[0];
		}
		T* operator->() const
		{
			return &ioiList[0];
		}
		inOrderIterator(
	};
	
	
	
	
	for the in order may make a array of pointer so i can access like an array and when it's updated it's sync
	T* t = new T[size];

	
	
	*/
};