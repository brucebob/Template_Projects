#include <list>
#include <exception>
/*
*		TreapTree Data Struct
*		Use both the Heap propriety and the binary search tree propriety
*		keeps a balance tree so if the inserting element are sorted it's 
*		not a one sided tree
*/
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
	const static int MAXRANDOM = 100000;
	unsigned int treeSize;
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
	bool hasChild(Node<T>* node)
	{
		if(node->left != nullptr || node->right != nullptr)
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
		if(node->left != nullptr && node->right == nullptr)
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
		if(node->right != nullptr && node->left == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
public:
	~TreapTree()
	{
		clear();
	}
	TreapTree()
	{
		tree = nullptr;
		treeSize = 0;
	}
	TreapTree(const TreapTree& treeIn)
	{
		tree = copyTree(treeIn.tree);
		treeSize = treeIn.size;
	}
	const TreapTree& operator=(const TreapTree& treeIn)
	{	
		if(this != &treeIn)
		{
			clear();
			tree = copyTree(treeIn.tree);
			treeSize = treeIn.treeSize;
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
			// check to see if it needs to move up
			while(addedNode->parent != nullptr && addedNode->priority > addedNode->parent->priority)
			{
				Node<T>* parent = addedNode->parent;

				// need to check what side it is on.
				// then rotate them either left or right.
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
		treeSize++;
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
		treeSize++;
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
	T* find(const TT& t)
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
	const T* find(const TT& t) const
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
	bool remove(const TT& t)
	{
		Node<T>* element = findNode(tree, t);
		if(element != nullptr)
		{		
			// checks to see if it's a leaf node
			Node<T>* parent = element->parent;
			if(!hasChild(element))
			{
				// it's a leaf node but not the root
				if(parent != nullptr)
				{
					if(parent->left == element)
					{
						parent->left = nullptr;
					}
					else
					{
						parent->right = nullptr;
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
						if(parent->left == element)
						{
							parent->left = element->left;
							parent->left->parent = parent;
						}
						else
						{
							parent->right = element->left;
							parent->right->parent = parent;
						}
					}
					else
					{
						tree = element->left;
						tree->parent = nullptr;
					}
					delete element;
				}
				// only has one right child
				else if(onlyRightChild(element))
				{
					if(parent != nullptr)
					{			
						if(parent->left == element)
						{
							parent->left = element->right;
							parent->left->parent = parent;
						}
						else
						{
							parent->right = element->right;
							parent->right->parent = parent;
						}
					}
					else
					{
						tree = element->right;
						tree->parent = nullptr;
					}
					delete element;
				}
				else
				{
					// has both left and right
					// have to find which has the max priority then that one comes first.
					// check to see what child goes first
					if(element->left->priority > element->right->priority)
					{
						if(parent != nullptr)
						{			
							if(parent->left == element)
							{
								parent->left = element->left;
								parent->left->parent = parent;
							}
							else
							{
								parent->right = element->left;
								parent->right->parent = parent;
							}
						}
						else
						{
							tree = element->left;
							tree->parent = nullptr;
						}
						
						// right will have to go into elements right
						balanceTree(element->left, element->right, false);
					}
					else
					{
						if(parent != nullptr)
						{			
							if(parent->right == element)
							{
								parent->right = element->right;
								parent->right->parent = parent;
							}
							else
							{
								parent->left = element->right;
								parent->left->parent = parent;
							}
						}
						else
						{
							tree = element->right;
							tree->parent = nullptr;
						}
						// left will have to go into elements left
						balanceTree(element->right, element->left, true);
					}
					delete element;
				}
			}
			treeSize--;
			return true;
		}
		return false;
	}
	// heres where i need to finsish
	void balanceTree(Node<T>* fixedNode, Node<T>* node, bool left) 
	{
		Node<T>* transPtr = fixedNode;
		if(left)
		{
			while(transPtr->left != nullptr && transPtr->left->priority > node->priority)
			{
				transPtr = transPtr->left;
			}

			if(transPtr->left != nullptr && node->left != nullptr)
			{
				if(transPtr->priority < node->priority)
				{
					balanceTree(transPtr->left, node->left, true);
				}
				else
				{

				}
			}
			else if(transPtr->left != nullptr)
			{
				node->left = transPtr->left;
				node->left->parent = node;
				transPtr->left = node;
				transPtr->left->parent = transPtr;
			}
			else
			{
				transPtr->left = node;
				transPtr->left->parent = transPtr;
			}
		}
		else
		{
			while(transPtr->right != nullptr && transPtr->right->priority < node->priority)
			{
				transPtr = transPtr->right;
			}

			if(transPtr->right != nullptr && node->right != nullptr)
			{
				// need to rebalance it from here
				int x;
			}
			else if(transPtr->right != nullptr)
			{
				node->right = transPtr->right;
				node->right->parent = node;
				transPtr->right = node;
				transPtr->right->parent = transPtr;
			}
			else
			{
				transPtr->right = node;
				node->parent = transPtr;
			}
		}
	}
	template<typename TT>
	bool remove(const TT && t)
	{
		Node<T>* element = findNode(tree, t);
		if(element != nullptr)
		{		
			// checks to see if it's a leaf node
			Node<T>* parent = element->parent;
			if(!hasChild(element))
			{
				// it's a leaf node but not the root
				if(parent != nullptr)
				{
					if(parent->left == element)
					{
						parent->left = nullptr;
					}
					else
					{
						parent->right = nullptr;
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
						if(parent->left == element)
						{
							parent->left = element->left;
							parent->left->parent = parent;
						}
						else
						{
							parent->right = element->left;
							parent->right->parent = parent;
						}
					}
					else
					{
						tree = element->left;
					}
					delete element;
				}
				// only has one right child
				else if(onlyRightChild(element))
				{
					if(parent != nullptr)
					{			
						if(parent->left == element)
						{
							parent->left = element->right;
							parent->left->parent = parent;
						}
						else
						{
							parent->right = element->right;
							parent->right->parent = parent;
						}
					}
					else
					{
						tree = element->right;
					}
					delete element;
				}
				else
				{
					// has both left and right
					// have to find which has the max priority then that one comes first.
					Node<T>* side = nullptr;
					
					if(parent != nullptr)
					{			
						if(parent->left == element)
						{
							side = parent->left;
						}
						else
						{
							side = parent->right;
						}
					}
					else
					{
						side = tree;
					}
				
					// check to see what child goes first
					if(element->left->priority > element->right->priority)
					{
						side = element->left;
						element->left->parent = parent;
						// right will have to go into elements right
						balanceTree(element->left, element->right, false);
					}
					else
					{
						side = element->right;
						element->right->parent = parent;
						// left will have to go into elements left
						balanceTree(element->right, element->left, true);
					}
					delete element;
				}
			}
			treeSize--;
			return true;
		}
		return false;
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
	unsigned int size() const
	{
		return treeSize;
	}
};