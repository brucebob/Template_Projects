#pragma once

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
	Node<T>* Tree;
public:
	BSTree<T>()
	{
		Tree = nullptr;
	}
	BSTree<T>(const BSTree<T>& TreeIn)
	{

	}
	const BSTree<T>& operator =(const BSTree<T>& TreeIn)
	{

	}
	void addElement(const T& elementIn)
	{

	}
	void addElement(T && elementIn)
	{

	}
	template<typename TT>
	const T& FindElement(const TT& t)
	{

	}
};