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
		int priority;
	};
public:
	~TreapTree()
	{

	}
	TreapTree()
	{

	}
	TreapTree(const TreapTree& treeIn)
	{

	}
	const TreapTree& operator=(const TreapTree& treeIn)
	{

	}
	void add(const T && t)
	{

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