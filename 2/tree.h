#pragma once
#include <iostream>
const int MAX_SIZE_OF_CHARS = 256;

using ull = unsigned long long;

struct TNode {
	struct TNode *left, *right, *parent; // Указатели на узлы
	int ind; // Какой проверяем индекс в бинарном числе
	//char key[MAX_SIZE_OF_CHARS]; // Ключ
	char * key; // Ключ
	ull value; // Само значение

	~TNode() {
		std::cout << "I am deleted!\n";
		delete[] key;
	}

	bool operator==(TNode * t) {
		if (strcmp(t->key,key) == 0) return true;
		return false;
	}
	
	void Set(char * t) {
		for (int i = 0; i < MAX_SIZE_OF_CHARS; i++)
		{
			key[i] = t[i];
		}
	}
};
// Ф-ия добавления узла в дерево
//void AddNode(TNode * startNode, TNode * newNode);
//TNode * AddNode(TNode * startNode, TNode * newNode);


TNode * SearchNode(TNode * startNode, char * key);
TNode * SearchNode(TNode * startNode, TNode & prevNode, bool & isLeaf);

//TNode * SearchNode(TNode * startNode, char * key, TNode & prevFind);

//TNode * SearchNode(TNode * startNode, char * key);
TNode * InsertNode(TNode * startNode, TNode * newNode);
TNode * DeleteNode(TNode * startNode, char * keyIn);

void TreeDelete(TNode * node);
void PrintTree(TNode * root, int line);

/*
           TEST {1} 82
							81 (1)
			70 (2)
	65(5)			*90 (3)
			   
*/

/*
		   TEST {1} 82
							81 (1)
			70 (2)
	65(5)			*90 (3)

*/