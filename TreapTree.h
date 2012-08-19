#include <list>
/*
*		TreapTree Data Struct
*		Use both the Heap propriety and the binary search tree propriety
*/

template<typename T>
class TreapTree
{
private:
	template<typename T> 
	struct Node
	{
		struct Node<T>* left;
		struct Node<T>* right;
		struct Node<T>* parent;
		T t;
		int priority;
	};
	const static int MAXRANDOM = INT_MAX - 1;
	Node<T> tree;
	int nextRandom()
	{
		return (int)rand() % MAXRANDOM;
	}
	Node<T>* makeNode(const T& t)
	{
		Node<T>* newNode;
		if(newNode != nullptr)
		{
		newNode->t = t;
		newNode->parent = nullptr;
		newNode->right = nullptr;
		newNode->left = nullptr;
		priority = nextRandom();
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
		clear();
		if(!treeIn.isEmpty())
		{
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
			tree = newNode(t);
		}
		else
		{
			Node<T>* transPtr = tree;
			if(transPtr->t > t)
			{
				if(transPtr->left == nullptr)
				{
					transPtr->left = makeNode(t);
					transPtr->left->parent = transPtr->left;
					// it's added and now it need to peculate up based on the priority
					if(transPtr->left->priority > transPtr->priority)
					{
						// then the left 
						Node<T>* temp = transPtr->left;
						temp->right = transPtr;
						temp->parent = transPtr->parent;
						transPtr->parent = temp;
					}
					return;
				}
				transPtr = transPtr->left;
			}
			else
			{
				if(transPtr->right == nullptr)
				{
					transPtr->right = makeNode(t);
					transPtr->right->parent = transPtr->right;
					// it's added and now it need to peculate up based on the priority
					if(transPtr->right->priority > transPtr->priority)
					{
						Node<T>* temp = transPtr->right;
						temp->left = transPtr;
						temp->parent = transPtr->parent;
						transPtr->parent = temp;
					}
					return;
				}
				transPtr = transPtr->right;
			}
		}
	}
	void add(const T& t)
	{

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