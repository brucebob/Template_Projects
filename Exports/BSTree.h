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
		// need a copy of the bst struct with a BFS
		tree = nullptr;
		if(!TreeIn.isEmpty())
		{
			std::list<Node<T>*> stack;
			stack.push_back(TreeIn.tree);
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
				add(transPtr->d);
				stack.pop_front();
			}
		}
	}
	const BSTree<T>& operator =(const BSTree<T>& TreeIn)
	{
		// need a deep copy of the pointers
		if(this != &TreeIn)
		{
			// if the tree is not empty i need to remove the old tree
			if(tree != nullptr)
			{
				clear();
			}

			if(!TreeIn.isEmpty())
			{
				// i'll need the bfs to make the new tree
				std::list<Node<T>*> stack;
				stack.push_back(TreeIn.tree);
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
					add(transPtr->d);
					stack.pop_front();
				}
			}
		}
		return *this;
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
};