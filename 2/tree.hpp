#pragma once
#include <iostream>
#include <cstring>
#include <fstream>

const int MAX_SIZE_OF_CHARS = 256;
typedef unsigned long long ull;
//using ull = uint64_t;
namespace trie{

	struct TNode {
		struct TNode *left, *right, *parent;
		int ind;
		char * key;
		ull value;

		~TNode() {
			delete[] key;
		}

		bool operator==(TNode * t) {
			if (strcmp(t->key,key) == 0) return true;
			return false;
		}

		void Set(char * t) {
			for (int i = 0; i < MAX_SIZE_OF_CHARS+1; i++)
			{
				key[i] = t[i];
			}
		}
	};

	TNode * SearchNode(TNode * startNode, char * key);
	TNode * SearchNode(TNode * startNode, TNode & prevNode, bool & isLeaf);

	TNode * InsertNode(TNode * startNode, TNode * newNode, bool needOK = true);
	TNode * DeleteNode(TNode * startNode, char * keyIn);

	void TreeDelete(TNode * node);
	void PrintTree(TNode * root, int space);

	void Save(TNode * startNode, std::ofstream & file);
	TNode * Load(std::ifstream & file);
}