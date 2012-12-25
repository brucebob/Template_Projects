#pragma once
#include <exception>
#include "compare_function.h"
#include "LinkedList.h"
template<typename key, typename content, typename F = compare_int<key>>
class content_tree
{
private:
	struct node
	{
		key k;
		content c;
		struct node* left_branch;
		struct node* right_branch;
	};
	node* tree_head;
	unsigned int tree_size;
public:
	~content_tree()
	{
		clear();
	}
	content_tree() : tree_head(nullptr), tree_size(0)
	{

	}
	content_tree(const content_tree& t) : tree_size(nullptr)
	{

	}
	content_tree& operator=(const content_tree& t)
	{

	}
	content operator[](const key& k)
	{
		if(tree_head == nullptr)
		{
			tree_head = new node;
			tree_head->left_branch = tree_head->right_branch = nullptr;
			tree_head->k = k;
			return tree_head;
		}
		else
		{
			node* trans_ptr = tree_head;
			while(trans_ptr != nullptr)
			{
				int index = F()(trans_ptr->k, k);
				if(index == -1)
				{
					
					if(trans_ptr->left_branch == nullptr)
					{
						node* temp = new node;
						temp->left_branch = temp->right_branch = nullptr;
						temp->k = k;
						trans_ptr->left_branch = temp;
						return temp->c;
					}
					trans_ptr = trans_ptr->left_branch;
				}
				else if(index == 1)
				{
					if(trans_ptr->right_branch == nullptr)
					{
						node* temp = new node;
						temp->left_branch = temp->right_branch = nullptr;
						temp->k = k;
						trans_ptr->right_branch = temp;
						return temp->c;
					}
					trans_ptr = trans_ptr->right_branch;
				}
				else
				{
					return trans_ptr->c;
				}
			}
			throw std::exception("Something went really wrong if it got here.");
		}
	}
	/*const content operator[](const key&) const
	{

	}*/
	void clear()
	{
		// need to empty the tree_head.
		if(tree_head == nullptr)
		{
			return;
		}
		LinkedList<node*> hold_list;
		hold_list.push_front(tree_head);
		
		while(!hold_list.empty())
		{
			if(hold_list.front()->left_branch != nullptr)
			{
				hold_list.push_back(hold_list.front()->left_branch);
			}
			else if(hold_list.front()->right_branch != nullptr)
			{
				hold_list.push_back(hold_list.front()->right_branch);
			}
			delete hold_list.front();
			hold_list.pop_front();
		}
		tree_list = nullptr;
	}
};