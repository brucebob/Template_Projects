

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
};