#include "tree.h"

const int USE_FOR_BYTES = 126;
const int BYTES_OF_ONE_CHAR = 5;

int & GetMin(int & a, int & b) {
	if (a > b) {
		return b;
	}
	return a;
}

int FindDif(TNode * a, TNode * b,bool & isLeftForNew, int endInd = -1) {
	int startInd = a->ind + 1;
	if (endInd == -1) {
		endInd = GetMin(a->sizeOfKey,b->sizeOfKey) * BYTES_OF_ONE_CHAR;
	}
	else {
		endInd--;
	}

	char * ca = a->key, * cb = b->key;
	int numberOfChar = startInd / BYTES_OF_ONE_CHAR; // Какой символ из ключа будем брать
	int numberOfLetter = startInd % BYTES_OF_ONE_CHAR; // Какой бит из символа будем брать
	if (numberOfLetter == 0 && numberOfChar > 0) {
		numberOfChar -= 1;
		numberOfLetter = USE_FOR_BYTES;
	}
	while (startInd<= endInd) {
		int right = ((cb[numberOfChar] >> (BYTES_OF_ONE_CHAR - numberOfLetter)) & 1);
		if (((ca[numberOfChar] >> (BYTES_OF_ONE_CHAR - numberOfLetter)) & 1) != right) {
			if (right) {
				isLeftForNew = false;
			}
			else {
				isLeftForNew = true;
			}
			break;
		}

		numberOfLetter++;
		if (numberOfLetter == 6) {
			numberOfChar += 1;
			numberOfLetter = 1;
		}
		startInd++;
	}

	if (startInd > endInd) {
		return -1;
	}
	return startInd;
}

int FindZero(int t) {
	// I variation
	/*int curNum = MAX_NUMBER_OF_BYTES;
	for (int i = 0; i < 7; i++)
	{
		int check = t - curNum;
		if (check < 0) {
			return i;
		}

		t = check;
		curNum /= 2;
	}

	return -1;*/

	// II variation (faster )
	for (int i = 0; i < 7; i++)
	{
		char newI = t >> (6 - i) | USE_FOR_BYTES;
		if (newI == USE_FOR_BYTES) {
			return i;
		}
	}
	return -1;
}

//TNode * SearchNode(TNode * CurNode, char * key) {
//	if (!CurNode) {
//		return nullptr;
//	}
//
//	if (CurNode->key == key) {
//		return CurNode;
//	}
//
//	int curInd = CurNode->ind;
//	int indOfWord = curInd / 7, indOfLetter = curInd % 7;
//	if ((key[indOfWord] >> (6 - indOfLetter)) & 1) {
//		return SearchNode(CurNode->right,key);
//	}
//	else {
//		return SearchNode(CurNode->left, key);
//	}
//}

TNode * AddNode(TNode * startNode, TNode * newNode) {
	if (!startNode) {
		newNode->ind = 0;
		newNode->right = nullptr;
		newNode->left = newNode;
		return newNode;
	}	
 
	if (startNode->left == startNode) {
		bool isLeftForNew = false;
		int lel = FindDif(startNode, newNode, isLeftForNew);
		if (isLeftForNew) {
			newNode->left = newNode;
			newNode->right = startNode;
		}
		else {
			newNode->left = startNode;
			newNode->right = newNode;
		}
		newNode->ind = lel;
		newNode->parent = startNode;
		startNode->left = newNode;
		startNode->parent = newNode;
		return startNode;
	}

	return startNode;
	char * newKey = newNode->key;
	TNode * curNode = startNode->left;
	int prevInd = 0;
	//int curInd = curNode->ind;
	while (true) {
		if (*curNode == newNode) {
			std::cout << "Error!\n";
			break;
		}

		int curInd = curNode->ind;
		if (curInd <= prevInd) {

			break;
		}

		int indOfWord = curInd / BYTES_OF_ONE_CHAR, indOfLetter = curInd % BYTES_OF_ONE_CHAR;
		if (indOfLetter == 0) {
			indOfWord -= 1;
		}

		if ((newKey[indOfWord] >> (BYTES_OF_ONE_CHAR - indOfLetter) & 1)) {
			curNode = curNode->right;
		}
		else {
			curNode = curNode->left;
		}

		prevInd = curInd;
	}

	return startNode;
}