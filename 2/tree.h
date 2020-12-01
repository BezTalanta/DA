#pragma once
#include <iostream>
const int MAX_SIZE_OF_CHARS = 256;

using ull = unsigned long long;

struct TNode {
	struct TNode *left, *right, *parent; // ��������� �� ������
	int ind, sizeOfKey; // ����� ��������� ������ � �������� �����
	//char key[MAX_SIZE_OF_CHARS]; // ����
	char * key; // ����
	ull value; // ���� ��������

	~TNode() {
		std::cout << "I am deleted!\n";
	}

	bool operator==(TNode * t) {
		if (*key == *t->key) return true;
		return false;
	}
};

// �-�� ���������� ������� ���������� ���� � �����
int FindZero(int t);

// �-�� ���������� ���� � ������
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