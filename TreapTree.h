/*
*		TreapTree Data Struct
*		Use both the Heap propriety and the binary search tree propriety
*/

template<typename T>
class TreapTree
{
private:
	template<typename T>
	struct Node<T>
	{
		struct Node<T>* left;
		struct Node<T>* right;
		struct Node<T>* parent;
		T t;
		int priority;
	};

	Node<T> tree;
	Node<T> makeNode(const T& t;)
	{
		Node<T>* newNode;
		newNode->t = t;
		newNode->parent = nullptr;
		newNode->right = nullptr;
		newNode->left = nullptr;
	}
public:
	~TreapTree()
	{
		if(tree != nullptr)
		{
			// need to remove stuff

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

		}
	}
	void add(const T& t)
	{

	}
	void find(const T& t)
	{

	}
	template typename<TT>
	void find(const TT& t)
	{

	}
};