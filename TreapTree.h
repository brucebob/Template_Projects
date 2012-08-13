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
		newNode->t = t;
		newNode->parent = nullptr;
		newNode->right = nullptr;
		newNode->left = nullptr;
		priority = nextRandom();
		return newNode;
	}

public:
	~TreapTree()
	{
		if(tree != nullptr)
		{
			// BFS to remove node by a stack.
			std::list<Node<T>*> nodeStack;
			nodeStack.push_back(tree);

			while(!nodeStack.empty())
			{
				if(nodeStack.front()->left != nullptr)
				{
					nodeStack.push_back(nodeStack.front()->left);
				}
				if(nodeStack.front()->right != nullptr)
				{
					nodeStack.push_back(nodeStack.front()->right);
				}
				delete nodeStack.front();
				nodeStack.pop_front();
			}
		}
	}
	TreapTree()
	{
		tree = nullptr;
	}
	TreapTree(const TreapTree& treeIn)
	{

	}
	const TreapTree& operator=(const TreapTree& treeIn)
	{

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
	void find(const T& t)
	{

	}
	template<typename TT>
	void find(const TT& t)
	{

	}
};