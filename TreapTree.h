#include <list>
#include <limits.h>
/*
*		TreapTree Data Struct
*		Use both the Heap propriety and the binary search tree propriety
*		keeps a balance tree so if the inserting element are sorted it's 
*		not a one sided tree
*/
// need to develop a better design for the treaptree then the one i have then i'll refacor it.
template<typename T>
class TreapTree
{
private:
	template<typename T> 
	struct Node
	{
		T t;
		int priority;
		struct Node<T>* left;
		struct Node<T>* right;
		struct Node<T>* parent;
	};
	const static int MAXRANDOM = INT_MAX - 1;
	Node<T>* tree;
	int nextRandom()
	{
		return (int)rand() % MAXRANDOM;
	}
	Node<T>* makeNode(const T& t)
	{
		Node<T>* newNode = new Node<T>;
		if(newNode != nullptr)
		{
			newNode->t = t;
			newNode->parent = nullptr;
			newNode->right = nullptr;
			newNode->left = nullptr;
			newNode->priority = nextRandom();
			return newNode;
		}
		else
		{
			throw std::bad_alloc("TreapTree: ran out of memory");
		}
	}
	Node<T>* makeNode(const T& t, int cPriority)
	{
		Node<T>* newNode;
		if(newNode != nullptr)
		{
			newNode->t = t;
			newNode->parent = nullptr;
			newNode->right = nullptr;
			newNode->left = nullptr;
			priority = cPriority;
			return newNode;
		}
		else
		{
			throw std::bad_alloc("TreapTree: ran out of memory");
		}
	}
	Node<T>* findNode(Node<T>* root, T t) const
	{
		Node<T>* transPtr = root;
		while(transPtr != nullptr)
		{
			if(transPtr->t > t)
			{
				transPtr = transPtr->left;
			}
			else if(transPtr->t < t)
			{
				transPtr = transPtr->right;
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
	void printTree(Node<T>* root)
	{
		std::list<Node<T>*> stack;
		stack.push_back(root);
		std::cout << std::endl;
		while(!stack.empty())
		{
			if(stack.front()->left != nullptr)
			{
				stack.push_back(stack.front()->left);
			}
			if(stack.front()->right != nullptr)
			{
				stack.push_back(stack.front()->right);
			}

			std::cout << stack.front()->t << " ";
			stack.pop_front();
		}
		std::cout << std::endl;
	}
public:
	~TreapTree()
	{
		clear();
	}
	TreapTree()
	{
		tree = nullptr;
	}
	TreapTree(const TreapTree& treeIn)
	{
		// need to run a bfs and then copy the prioritys
		
		tree = nullptr;
		if(!isEmpty())
		{
			std::list<Node<T>*> stack;
			stack.push_front(tree);
			while(!stack.empty())
			{
				if(stack.front()->left != nullptr)
				{
					stack.push_back(stack.front()->left);
				}
				if(stack.front()->right != nullptr)
				{
					stack.push_back(stack.front()->right);
				}
			}
			add(stack.front()->t, stack.front()->priority);
			stack.pop_front();
		}
	}
	const TreapTree& operator=(const TreapTree& treeIn)
	{
		
		if(this != &treeIn)
		{
			clear();
			if(treeIn.isEmpty())
			{
				return *this;
			}

			// need to copy the tree 
			std::list<Node<T>*> stack;
			stack.push_front(treeIn.tree);
			while(!stack.empty())
			{
				if(stack.front()->left != nullptr)
				{
					stack.push_back(stack.front()->left);
				}
				if(stack.front()->right != nullptr)
				{
					stack.push_back(stack.front()->right);
				}
			}
			add(stack.front()->t, stack.front()->priority);
			stack.pop_front();
		}
		return *this;
	}
	void add(const T && t)
	{
		if(tree == nullptr)
		{
			tree = makeNode(t);
		}
		else
		{
			Node<T>* transPtr = tree;
			Node<T>* addedNode = nullptr;
			while(transPtr != nullptr)
			{
				if(transPtr->t > t)
				{
					if(transPtr->left == nullptr)
					{
						transPtr->left = makeNode(t);
						transPtr->left->parent = transPtr;
						addedNode = transPtr->left;
						break;
					}
					transPtr = transPtr->left;
				}
				else
				{
					if(transPtr->right == nullptr)
					{
						transPtr->right = makeNode(t);
						transPtr->right->parent = transPtr;
						addedNode = transPtr->right;
						break;
					}
					transPtr = transPtr->right;
				}
			}
			while(addedNode->parent != nullptr && addedNode->priority > addedNode->parent->priority)
			{
				// swap the parent and the new node
				Node<T>* temp = addedNode->parent;
				addedNode->parent = temp->parent;
				temp->parent = addedNode;
				// now i'll have to swap the leaves.
			}
		}
	}
	void add(const T& t)
	{
		if(tree == nullptr)
		{
			tree = makeNode(t);
		}
		else
		{
			Node<T>* transPtr = tree;
			Node<T>* addedNode = nullptr;
			while(transPtr != nullptr)
			{
				if(transPtr->t > t)
				{
					if(transPtr->left == nullptr)
					{
						transPtr->left = makeNode(t);
						transPtr->left->parent = transPtr;
						addedNode = transPtr->left;
						break;
					}
					transPtr = transPtr->left;
				}
				else
				{
					if(transPtr->right == nullptr)
					{
						transPtr->right = makeNode(t);
						transPtr->right->parent = transPtr;
						addedNode = transPtr->right;
						break;
					}
					transPtr = transPtr->right;
				}
			}
			// check to see if it needs to move up
			while(addedNode->parent != nullptr && addedNode->priority > addedNode->parent->priority)
			{
				Node<T>* parent = addedNode->parent;

				// need to check what side it is on.
				// then rotate them either left or right.
				printTree(tree);
				if(parent->left == addedNode)
				{
					if(parent == tree)
					{
						tree = RotateLeft(tree, parent, addedNode);
					}
					else
					{
						addedNode = RotateLeft(tree, parent, addedNode);
					}
				}
				else if(parent->right == addedNode)
				{
					// have to see if the head pointer is being change as it wont be seen if any changes are made to it
					if(parent == tree)
					{
						tree = RotateRight(tree, parent, addedNode);
					}
					else
					{
						addedNode = RotateRight(tree, parent, addedNode);
					}
				}
			}
		}
	}
	Node<T>* RotateLeft(Node<T>* treedata, Node<T>* parent, Node<T>* child) 
	{
		bool swapedChilds = false;
		if(child->right != nullptr)
		{
			parent->left = child->right;
			parent->left->parent = parent;
			swapedChilds = true;
		}
		child->parent = parent->parent;
		child->right = parent;		
		swapPositionInParent(parent, child);
		parent->parent = child;
		if(!swapedChilds)
		{
			parent->left = nullptr;
		}
		return child;
	}
	Node<T>* RotateRight(Node<T>* treedata, Node<T>* parent, Node<T>* child) 
	{
		bool swapedChilds = false;
		// handles children
		if(child->left != nullptr)
		{
			parent->right = child->left;
			parent->right->parent = parent;
			swapedChilds = true;
		}
		child->parent = parent->parent;
		child->left = parent;		
		swapPositionInParent(parent, child);
		parent->parent = child;
		if(!swapedChilds)
		{
			parent->right = nullptr;
		}
		return child;
	}
	void swapPositionInParent(Node<T>* parent, Node<T>* child) 
	{
		if(parent->parent != nullptr)
		{
			if(parent->parent->right == parent)
			{
				parent->parent->right = child;
			}
			else if(parent->parent->left == parent)
			{
				parent->parent->left = child;
			}
		}
	}
	template<typename TT>
	T* findElement(const TT& t)
	{
		if(tree != nullptr)
		{
			return &findNode(tree, t)->t; 
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
	bool isEmpty() const
	{
		return tree == nullptr;
	}
	void clear()
	{
		if(!isEmpty())
		{
			// BFS to remove node by a stack.
			std::list<Node<T>*> stack;
			stack.push_back(tree);

			while(!stack.empty())
			{
				if(stack.front()->left != nullptr)
				{
					stack.push_back(stack.front()->left);
				}
				if(stack.front()->right != nullptr)
				{
					stack.push_back(stack.front()->right);
				}
				delete stack.front();
				stack.pop_front();
			}
			tree = nullptr;
		}
	}
};