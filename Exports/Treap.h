#pragma once

template<typename T>
class TreapTree
{
private:
	template<typename T>
	struct Node
	{
		T data;
		unsigned int proirty;
		struct Node<T>* parent;
		struct Node<T>* left;
		struct Node<T>* right;
	};
	Node<T>* tree;
public:
	TreapTree<T>()
	{
		tree = nullptr;
	}
	void add(T item)
	{

	}
	TreapTree<T>(const TreapTree<T>& treeIn)
	{

	}
	TreapTree<T>& operator=(const TreapTree<T>& treeIn)
	{
		return *this;
	}
};