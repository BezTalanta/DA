#include "tree.h"

const int USE_FOR_BYTES = 126;
const int BYTES_OF_ONE_CHAR = 5;

int & GetMin(int & a, int & b) {
	if (a > b) {
		return b;
	}
	return a;
}

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

TNode * SearchNode(TNode * needToFoundOwner,bool & isLeaf, bool & isLeftForFoundNode) {
	char * keyIn = needToFoundOwner->key;
	
	int prevInd = -1;
	if (needToFoundOwner->ind == 0) {
		needToFoundOwner = needToFoundOwner->left;
		prevInd = 0;
	}

	int curInd = needToFoundOwner->ind;
	while (curInd > prevInd) {
		int indOfWord = curInd / BYTES_OF_ONE_CHAR, indOfLetter = curInd % BYTES_OF_ONE_CHAR;
		if (indOfLetter == 0) { indOfWord--, indOfLetter = BYTES_OF_ONE_CHAR; }
	
		if ((keyIn[indOfWord] >> (BYTES_OF_ONE_CHAR - indOfLetter)) & 1) {
			if (strcmp(needToFoundOwner->right->key, keyIn) == 0) {
				if (prevInd == -1) {
					isLeaf = true;
				}
	
				isLeftForFoundNode = false;
				return needToFoundOwner;
			}
	
			needToFoundOwner = needToFoundOwner->right;
		}
		else {
			if (strcmp(needToFoundOwner->left->key,keyIn) == 0) {
				if (prevInd == -1) {
					isLeaf = true;
				}
	
				isLeftForFoundNode = true;
				return needToFoundOwner;
			}
	
			needToFoundOwner = needToFoundOwner->left;
		}
	
		prevInd = curInd;
		curInd = needToFoundOwner->ind;
	}

	return needToFoundOwner;
}

//TNode * SearchNode(TNode * startNode, TNode & prevNode, bool & isLeaf) {
//	if (!startNode) {
//		return nullptr;
//	}
//
//	char * keyIn = startNode->key;
//
//	if (startNode->ind == 0) {
//		startNode = startNode->left;
//	}
//
//	int curInd = startNode->ind, prevInd = -1;
//	while (curInd > prevInd) {
//		int indOfWord = curInd / BYTES_OF_ONE_CHAR, indOfLetter = curInd % BYTES_OF_ONE_CHAR;
//		if (indOfLetter == 0) { indOfWord--, indOfLetter = BYTES_OF_ONE_CHAR; }
//
//		if ((keyIn[indOfWord] >> (BYTES_OF_ONE_CHAR - indOfLetter)) & 1) {
//			if (strcmp(startNode->right->key, keyIn) == 0) {
//				if (prevInd == -1) {
//					isLeaf = true;
//				}
//
//				prevNode = *startNode;
//				return startNode->right;
//			}
//
//			startNode = startNode->right;
//		}
//		else {
//			if (strcmp(startNode->left->key,keyIn) == 0) {
//				if (prevInd == -1) {
//					isLeaf = true;
//				}
//
//				prevNode = *startNode;
//				return startNode->left;
//			}
//
//			startNode = startNode->left;
//		}
//
//		prevInd = curInd;
//		curInd = startNode->ind;
//	}
//
//	return nullptr;
//}

TNode * SearchNode(TNode * startNode, char * key) {
	if (!startNode) {
		return nullptr;
	}

	TNode * curNode = startNode->left, * prevNode = startNode;
	int prevInd = 0, curInd = curNode->ind, maxInd = strlen(key) * BYTES_OF_ONE_CHAR;
	while (curInd > prevInd) {
		int indOfWord = curInd / BYTES_OF_ONE_CHAR, indOfLetter = curInd % BYTES_OF_ONE_CHAR;
		if (indOfLetter == 0) indOfWord--,indOfLetter = BYTES_OF_ONE_CHAR;

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
			prevNode = curNode;
			curNode = curNode->right;
		}
		else {
			//if (curNode->left->ind <= maxInd) { // Neyveren v etom
			//	curNode = curNode->left;
			//}
			//else {
			//	break;
			//}
			prevNode = curNode;
			curNode = curNode->left;
		}

		prevInd = curInd;
		curInd = curNode->ind;
	}

	/*if (&prevFind) {
		prevFind = *prevNode;
	}*/

	return curNode;
}

TNode * InsertNode(TNode * startNode, TNode * newNode) {
	if (!startNode) {
		newNode->left = newNode;
		newNode->right = nullptr;
		newNode->parent = nullptr;
		newNode->ind = 0;
		std::cout << "OK\n";
		return newNode;
	}

	TNode * foundNode = SearchNode(startNode,newNode->key);
	if (*foundNode == newNode) {
		std::cout << "Error: node is already exist!\n";
		return startNode;
	}

	// Bool in order know the direction of the right arrow of the newNode
	bool isOneForNewNode = false;
	int dif = GetDifference(foundNode,newNode,isOneForNewNode);
	std::cout << "Dif ind: " << dif << ' ';
	newNode->ind = dif;

	TNode * curN = startNode->left, * prevN = startNode;
	int prevInd = 0, curInd = curN->ind;
	bool isPrevLeftEqualCurrent = true;
	char * c = newNode->key;

	// Finding a pair of nodes for inserting a newNode
	while (curInd > prevInd && curInd < dif) {
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
	newNode->parent = prevN;

	if (curN->ind > prevN->ind) {
		curN->parent = newNode;
	}	

	std::cout << "OK\n";
	return startNode;
}

TNode * DeleteNode(TNode * startNode, char * keyIn) { // a w q p
	if (!startNode) {
		std::cout << "Error: tree is empty!\n";
		return startNode;
	}
	
	if (startNode->left == startNode) {
		delete startNode;
		std::cout << "Ok!\n";
		return nullptr;
	}

	TNode * foundNode = SearchNode(startNode,keyIn);
	if (strcmp(foundNode->key, keyIn) != 0) {
		std::cout << "Error: can't find " << keyIn << " node!\n";
		return startNode;
	}

	if (foundNode == startNode) { 
		bool isLeafTmp = false, isLeftForNodeTmp = false;
		TNode * foundNodeNew = SearchNode(foundNode, isLeafTmp, isLeftForNodeTmp);

		bool isLeafTmp2 = false, isLeftForNodeTmp2 = false;
		TNode * foundNodeNew2 = SearchNode(foundNodeNew, isLeafTmp2, isLeftForNodeTmp2);

		if (foundNodeNew->parent != startNode) { // Узел на хед не левый узел хеда
			if (isLeftForNodeTmp) { // Узел на хед идет указатель слева
				if (foundNodeNew->parent->right == foundNodeNew) { // Отец узла идет вправо для нахождения нашего узла
					if (!isLeafTmp2) { // Узел на найденный узел не лист
						foundNodeNew->parent->right = foundNodeNew->right;
						foundNodeNew->right->parent = foundNodeNew->parent;
					}
					else {
						foundNodeNew->parent->right = startNode;
					}
				}
				else { // Отец узла идет влево для нахождения нашего узла
					if (!isLeafTmp2) { // Узел на узел не лист
						foundNodeNew->parent->left = foundNodeNew->right;
						foundNodeNew->right->parent = foundNodeNew->parent;
					}
					else {
						foundNodeNew->parent->left = startNode;
					}
				}
			}
			else { // Узел на хед идет указатель слева
				if (foundNodeNew->parent->right == foundNodeNew) { // Отец узла идет вправо для нашего узла
					if (!isLeafTmp2) { // Лист узел на узел
						foundNodeNew->parent->right = foundNodeNew->left;
						foundNodeNew->left->parent = foundNodeNew->parent;
					}
					else{
						foundNodeNew->parent->right = startNode;
					}
				}
				else { // Отец узла идет влево для нашего узла
					if (!isLeafTmp2) {
						foundNodeNew->parent->left = foundNodeNew->left;
						foundNodeNew->left->parent = foundNodeNew->parent;
					}
					else {
						foundNodeNew->parent->left = startNode;
					}
				}
			}

			startNode->Set(foundNodeNew->key);
			startNode->value = foundNodeNew->value;
			
			delete foundNodeNew;

			if (isLeftForNodeTmp2) {
				foundNodeNew2->left = startNode;
			}
			else {
				foundNodeNew2->right = startNode;
			}

			std::cout << "Ok\n";
			return startNode;
		}
		else {
			foundNodeNew->ind = 0;
			if (isLeftForNodeTmp) {
				foundNodeNew->left = foundNodeNew->right;
			}

			foundNodeNew->right = nullptr;
			foundNodeNew->parent = nullptr;
			delete startNode;
			std::cout << "Ok\n";
			return foundNodeNew;
		}
	}

	bool isLeaf = false, isLeftForNode = false;
	TNode * foundNodeNew = SearchNode(foundNode, isLeaf, isLeftForNode);
	while (!isLeaf) {
		foundNode->Set(foundNodeNew->key);
		foundNode->value = foundNodeNew->value;
		foundNode = foundNodeNew;

		foundNodeNew = SearchNode(foundNode, isLeaf, isLeftForNode);
	}	

	if (isLeftForNode) {
		TNode * justCheck = foundNodeNew->parent;
		if (justCheck->left == foundNodeNew) {
			justCheck->left = foundNodeNew->right;
		}
		else {
			justCheck->right = foundNodeNew->right;
		}
	}
	else {
		TNode * justCheck = foundNodeNew->parent;
		if (justCheck->left == foundNodeNew) {
			justCheck->left = foundNodeNew->left;
		}
		else {
			justCheck->right = foundNodeNew->left;
		}
	}


	delete foundNodeNew;

	std::cout << "Ok\n";

	/*std::cout << "Del func found node:\nkey: " << foundNode->key << "\nid: " << foundNode->ind << "\null: " << foundNode->value << "\n\n";
	std::cout << "Del func found prev node:\nkey: " << foundNodeNew->key << "\nid: " << foundNodeNew->ind << "\null: " << foundNodeNew->value << '\n';

	std::cout << "Is " << foundNodeNew->key << " leaf: "<< (bool)isLeaf << '\n';
	std::cout << "Left for " << foundNodeNew->key << " is: " << foundNode->key << " is-> " << (bool)isLeftForNode << '\n';*/

	return startNode;
}

void TreeDelete(TNode * node) {
	std::cout << "Delete it: " << node->key << '\n';
	if (!node) {
		return;
	}

	int nodeInd = node->ind;
	if (node->left->ind > nodeInd) {
		TreeDelete(node->left);
	}

	if (node->right != nullptr && node->right->ind > nodeInd) {
		TreeDelete(node->right);
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
		std::cout << "\"" << root->right->key << "\", ";
	}
	else {
		std::cout << "\"nullptr\", ";
	}

	if (root->parent != nullptr) {
		std::cout << "\"" << root->parent->key << "\")\n";
	}
	else {
		std::cout << "\"nullptr\")\n";
	}

	int ind = root->ind;
	if (root->right != nullptr && root->right->ind > ind) {
		line++;
		PrintTree(root->right, line);
	}

	if (root->left->ind > ind) {
		line++;
		PrintTree(root->left, line);
	}
}