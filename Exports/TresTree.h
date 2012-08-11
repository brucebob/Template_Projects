#pragma once
/*
#include <string>
#include "List.h"

class TresTree
{
private:
	typedef struct Node
	{
		bool word;
		SortedList<int> LettersUsed;
		struct Node** level;
	}TNode;
	// if i could make this smaller i build a faster struct.
	const static short CharSize = 96;
	const static char OffSet = 32;
	TNode* T;
	TNode* init()
	{
		TNode* node = new TNode;
		node->level = new TNode* [CharSize];
		node->word = false;
		
		for(unsigned int x = 0; x < CharSize; x++)
		{
			node->level[x] = nullptr;
		}

		return node;
	}
	bool cWord(TNode* Tin, const std::string& word) const
	{
		if(word.length() != 0)
		{
			char k = word.at(0) - OffSet;
			if(Tin->level[k] != nullptr)
			{
				return cWord(Tin->level[k], word.substr(1, word.length() - 1));
			}
			else
			{
				return false;
			}
		}
		else
		{
			return Tin->word;
		}
	}
	void aWord(TNode* Tin, const std::string& word)
	{
		if(word.size() != 0)
		{
			char k = word.at(0) - OffSet;
			if(Tin->level[k] == nullptr)
			{
				Tin->level[k] = init();
				Tin->LettersUsed.push(k);
			}
			aWord(Tin->level[k], word.substr(1, word.length() - 1));
		}
		else
		{
			Tin->word = true;
		}
	}
	void DeleteNode(TNode* Tin)
	{
		while(!Tin->LettersUsed.isEmpty())
		{
			int spot = Tin->LettersUsed.pop();
			
			DeleteNode(Tin->level[spot]);
		}
		delete [] Tin->level;
		delete Tin;
		Tin = nullptr;
	}
	TNode* Copy(TNode* t)
	{
		TNode* NTrest = init();
		NTrest->word = t->word;
		for(SortedList<int>::Const_ListIterator cItor = t->LettersUsed.const_front(); cItor != nullptr; cItor++)
		{
			NTrest->LettersUsed.push(*cItor);
			NTrest->level[*cItor] = Copy(t->level[*cItor]);
		}
		return NTrest;
	}
	TresTree(TNode* t)
	{
		T = t;
	}
public:
	~TresTree()
	{
		DeleteNode(T);
	}
	TresTree()
	{
		T = init();
	}
	void clear()
	{
		DeleteNode(T);
		T = init();
	}
	bool compareWord(std::string s) const
	{
		return cWord(T,s);
	}
	void addWord(std::string s)
	{
		aWord(T,s);
	}
	TresTree& operator=(const TresTree& t )
	{
		if(this != &t)
		{
			// need to clear the old stuff out first.
			DeleteNode(T);
			T = Copy(t.T);
		}
		return *this;
	}
	TresTree(const TresTree& t)
	{
		T = Copy(t.T);	
	}
};

// C version
/*

typedef struct trie
{
	int word;
	struct trie** edges;
} TTree;
void addWord(TTree* Tin, char* word);
void init(TTree** Tin);
bool compare(TTree* Tin, char* word);


void init(TTree** Tin)
{
	*Tin = (TTree*)malloc(sizeof(TTree));
	(*Tin)->edges = (TTree**)malloc(26 * sizeof(TTree*));
	(*Tin)->word = 0;
	for(int x = 0; x < 27; x++)
	{
		(*Tin)->edges[x] = NULL;
	}
}
void addWord(TTree* Tin, char* word)
{
	if(strlen(word) != 0)
	{
		int k = word[0] - 97;
		if(Tin->edges[k] == NULL)
		{
			Tin->edges[k] = (TTree*)malloc(sizeof(TTree));
			init(&Tin->edges[k]);
		}
		addWord(Tin->edges[k], word + 1);
	}
	else
	{
		Tin->word += 1;
	}
}
bool compare(TTree* Tin, char* word)
{
	if(strlen(word) != 0)
	{
		int k = word[0] - 97;

		if(Tin->edges[k] != NULL)
		{
			return compare(Tin->edges[k], word + 1);
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(Tin->word != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

*/