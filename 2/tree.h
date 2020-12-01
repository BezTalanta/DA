#pragma once
#include <iostream>
const int MAX_SIZE_OF_CHARS = 256;

using ull = unsigned long long;

struct TNode {
	struct TNode *left, *right, *parent; // Указатели на листья
	int ind, sizeOfKey; // Какой проверяем индекс в бинарном числе
	//char key[MAX_SIZE_OF_CHARS]; // Ключ
	char * key; // Ключ
	ull value; // Само значение

	~TNode() {
		std::cout << "I am deleted!\n";
	}

	bool operator==(TNode * t) {
		if (*key == *t->key) return true;
		return false;
	}
};

// Ф-ия нахождения первого побитового нуля в числе
int FindZero(int t);

// Ф-ия добавления узла в дерево
//void AddNode(TNode * startNode, TNode * newNode);
TNode * AddNode(TNode * startNode, TNode * newNode);

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