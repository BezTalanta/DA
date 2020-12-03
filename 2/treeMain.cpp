#include "tree.h"

const int USE_FOR_BYTES = 126;
const int BYTES_OF_ONE_CHAR = 5;

int & GetMin(int & a, int & b) {
	if (a > b) {
		return b;
	}
	return a;
}

//int FindDif(TNode * a, TNode * b,bool & isLeftForNew, int endInd = -1) {
//	int startInd = a->ind + 1;
//	if (endInd == -1) {
//		endInd = GetMin(a->sizeOfKey,b->sizeOfKey) * BYTES_OF_ONE_CHAR;
//	}
//	else {
//		endInd--;
//	}
//
//	char * ca = a->key, * cb = b->key;
//	int numberOfChar = startInd / BYTES_OF_ONE_CHAR; // Какой символ из ключа будем брать
//	int numberOfLetter = startInd % BYTES_OF_ONE_CHAR; // Какой бит из символа будем брать
//	if (numberOfLetter == 0 && numberOfChar > 0) {
//		numberOfChar -= 1;
//		numberOfLetter = USE_FOR_BYTES;
//	}
//	while (startInd<= endInd) {
//		int right = ((cb[numberOfChar] >> (BYTES_OF_ONE_CHAR - numberOfLetter)) & 1);
//		if (((ca[numberOfChar] >> (BYTES_OF_ONE_CHAR - numberOfLetter)) & 1) != right) {
//			if (right) {
//				isLeftForNew = false;
//			}
//			else {
//				isLeftForNew = true;
//			}
//			break;
//		}
//
//		numberOfLetter++;
//		if (numberOfLetter == 6) {
//			numberOfChar += 1;
//			numberOfLetter = 1;
//		}
//		startInd++;
//	}
//
//	if (startInd > endInd) {
//		return -1;
//	}
//	return startInd;
//}

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

int GetDifference(TNode * a, TNode * b, bool & isOneForNewNode) {
	char *ac = a->key, *bc = b->key;
	int acLen = strlen(ac), bcLen = strlen(bc);
	int maxInd = GetMin(acLen, bcLen) * BYTES_OF_ONE_CHAR;
	int indOfWord = 0, indOfLetter = 1;
	for (int i = 1; i <= maxInd; i++)
	{
		indOfWord = i / BYTES_OF_ONE_CHAR;
		if (i % BYTES_OF_ONE_CHAR == 0) {
			indOfWord--;
			indOfLetter = 5;
		}

		int checkForNew = (bc[indOfWord] >> (BYTES_OF_ONE_CHAR - indOfLetter) & 1);
		if ((ac[indOfWord] >> (BYTES_OF_ONE_CHAR - indOfLetter) & 1) != checkForNew) {
			if (checkForNew) {
				isOneForNewNode = true;
			}
			return i;
		}

		if (indOfLetter == BYTES_OF_ONE_CHAR) {
			indOfLetter = 1;
		}
		else {
			indOfLetter++;
		}
	}

	// Find the difference between two chars of different lengths
	char getLastChar;
	if (acLen < bcLen) {
		getLastChar = bc[indOfWord + 1]-96;
		isOneForNewNode = true;
	}
	else {
		getLastChar = ac[indOfWord + 1]-96;
	}

	if (getLastChar >= 16) return (indOfWord + 1) * BYTES_OF_ONE_CHAR + 1;
	if (getLastChar >= 8) return (indOfWord + 1) * BYTES_OF_ONE_CHAR + 2;
	if (getLastChar >= 4) return (indOfWord + 1) * BYTES_OF_ONE_CHAR + 3;
	if (getLastChar >= 2) return (indOfWord + 1) * BYTES_OF_ONE_CHAR + 4;
	return (indOfWord + 1) * BYTES_OF_ONE_CHAR + 5;
}

TNode * SearchNode(TNode * startNode, char * key) {
	if (!startNode) {
		return nullptr;
	}

	TNode * curNode = startNode->left;
	int prevInd = 0, curInd = curNode->ind, maxInd = strlen(key) * BYTES_OF_ONE_CHAR;
	while (curInd > prevInd) {
		int indOfWord = curInd / BYTES_OF_ONE_CHAR, indOfLetter = curInd % BYTES_OF_ONE_CHAR;
		if (indOfLetter == 0) indOfWord -= 1,indOfLetter = BYTES_OF_ONE_CHAR;

		if (curInd > maxInd) {
			key[indOfWord] = '\0';
		}

		if ((key[indOfWord] >> (BYTES_OF_ONE_CHAR - indOfLetter)) & 1) {
			//if (curNode->right->ind <= maxInd) { // Neyveren v etom
			//	curNode = curNode->right;
			//}
			//else {
			//	break;
			//}
			curNode = curNode->right;
		}
		else {
			//if (curNode->left->ind <= maxInd) { // Neyveren v etom
			//	curNode = curNode->left;
			//}
			//else {
			//	break;
			//}
			curNode = curNode->left;
		}

		prevInd = curInd;
		curInd = curNode->ind;
	}

	return curNode;
}

TNode * InsertNode(TNode * startNode, TNode * newNode) {
	if (!startNode) {
		newNode->left = newNode;
		newNode->right = nullptr;
		newNode->ind = 0;
		std::cout << "OK\n";
		return newNode;
	}

	TNode * foundNode = SearchNode(startNode,newNode->key);
	if (*foundNode == newNode) {
		std::cout << "Error: node is already exist!\n";
		return startNode;
	}

	// Бул для того, чтобы сразу знать направление правой стрелки нового нода
	bool isOneForNewNode = false; // Bool in order know the direction of the right arrow of the newNode
	int dif = GetDifference(foundNode,newNode,isOneForNewNode);
	std::cout << "Dif ind: " << dif << ' ';
	newNode->ind = dif;

	TNode * curN = startNode->left, * prevN = startNode;
	int prevInd = 0, curInd = curN->ind;
	bool isPrevLeftEqualCurrent = true;
	char * c = newNode->key;
	while (curInd > prevInd && curInd < dif) { // Finding a pair of nodes for inserting a newNode
		int indOfWord = curInd / BYTES_OF_ONE_CHAR, indOfLetter = curInd % BYTES_OF_ONE_CHAR;
		if (indOfLetter == 0) indOfWord -= 1, indOfLetter = BYTES_OF_ONE_CHAR;

		prevN = curN;
		if ((c[indOfWord] >> (BYTES_OF_ONE_CHAR - indOfLetter)) & 1) {
			curN = curN->right;
			isPrevLeftEqualCurrent = false;
		}
		else {
			curN = curN->left;
			isPrevLeftEqualCurrent = true;
		}

		prevInd = curInd;
		curInd = curN->ind;
	}

	if (isPrevLeftEqualCurrent) {
		prevN->left = newNode;
		if (isOneForNewNode) {
			newNode->right = newNode;
			newNode->left = curN;
		}
		else {
			newNode->left = newNode;
			newNode->right = curN;
		}
	}
	else {
		prevN->right = newNode;
		if (isOneForNewNode) {
			newNode->right = newNode;
			newNode->left = curN;
		}
		else {
			newNode->left = newNode;
			newNode->right = curN;
		}
	}

	std::cout << "OK\n";
	return startNode;
}

//TNode * AddNode(TNode * startNode, TNode * newNode) {
//	if (!startNode) {
//		newNode->ind = 0;
//		newNode->right = nullptr;
//		newNode->left = newNode;
//		return newNode;
//	}	
// 
//	if (startNode->left == startNode) {
//		bool isLeftForNew = false;
//		int lel = FindDif(startNode, newNode, isLeftForNew);
//		if (isLeftForNew) {
//			newNode->left = newNode;
//			newNode->right = startNode;
//		}
//		else {
//			newNode->left = startNode;
//			newNode->right = newNode;
//		}
//		newNode->ind = lel;
//		newNode->parent = startNode;
//		startNode->left = newNode;
//		startNode->parent = newNode;
//		return startNode;
//	}
//
//	return startNode;
//	char * newKey = newNode->key;
//	TNode * curNode = startNode->left;
//	int prevInd = 0;
//	//int curInd = curNode->ind;
//	while (true) {
//		if (*curNode == newNode) {
//			std::cout << "Error!\n";
//			break;
//		}
//
//		int curInd = curNode->ind;
//		if (curInd <= prevInd) {
//
//			break;
//		}
//
//		int indOfWord = curInd / BYTES_OF_ONE_CHAR, indOfLetter = curInd % BYTES_OF_ONE_CHAR;
//		if (indOfLetter == 0) {
//			indOfWord -= 1;
//		}
//
//		if ((newKey[indOfWord] >> (BYTES_OF_ONE_CHAR - indOfLetter) & 1)) {
//			curNode = curNode->right;
//		}
//		else {
//			curNode = curNode->left;
//		}
//
//		prevInd = curInd;
//	}
//
//	return startNode;
//}

void NodeDelete(TNode * node) {
	std::cout << "Delete it: " << node->key << '\n';
	if (!node) {
		return;
	}

	int nodeInd = node->ind;
	if (node->left->ind > nodeInd) {
		NodeDelete(node->left);
	}

	if (node->right != nullptr && node->right->ind > nodeInd) {
		NodeDelete(node->right);
	}

	std::cout << node->key << ": Successfully deleted\n";
	delete node;
}

// aa ahb ahc ap apr
// aa ao ag ae af ad
// abp abpp abppp

void PrintTree(TNode * root, int line) {
	if (!root) {
		return;
	}

	std::cout << line << ".\t" << root->key << " (" << root->ind << ", \"" << root->left->key << "\", ";
	if (root->right != nullptr) {
		std::cout << "\"" << root->right->key << "\")\n";
	}
	else {
		std::cout << "\"nullptr\")\n";
	}

	int ind = root->ind;
	if (root->right != nullptr && root->right->ind > ind) {
		PrintTree(root->right, ++line);
	}

	if (root->left->ind > ind) {
		PrintTree(root->left, ++line);
	}
}