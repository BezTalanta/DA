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
		delete newNode;
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

TNode * DeleteNode(TNode * startNode, char * keyIn) {
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

	bool isLeafTmp = false, isLeftForNodeTmp = false;
	TNode * foundNodeNew = SearchNode(foundNode, isLeafTmp, isLeftForNodeTmp);

	if(isLeafTmp){ // Когда удаляемый элемент - лист
		TNode * parentOfFoundNode = foundNode->parent;
		if(parentOfFoundNode->left == foundNode){
			if(isLeftForNodeTmp){
				//std::cout << "Flag1!\n";
				parentOfFoundNode->left = foundNode->right;
			}
			else{
				parentOfFoundNode->left = foundNode->left;
			}

			if(parentOfFoundNode->ind < parentOfFoundNode->left->ind){
				parentOfFoundNode->left->parent = parentOfFoundNode;
			}
		}
		else{
			if(isLeftForNodeTmp){
				//std::cout << "Flag3!\n";
				parentOfFoundNode->right = foundNode->right;
			}
			else{
				//std::cout << "Flag4!\n";
				parentOfFoundNode->right = foundNode->left;
			}

			if(parentOfFoundNode->ind < parentOfFoundNode->right->ind){
				parentOfFoundNode->right->parent = parentOfFoundNode;
			}
		}

		std::cout << "OK\n";
		delete foundNode;
		return startNode;
	}

	bool isLeafTmp2 = false, isLeftForNodeTmp2 = false;
	TNode * foundNodeNew2 = SearchNode(foundNodeNew, isLeafTmp2, isLeftForNodeTmp2);

	// Меняем значения первого нода на значения второго
	foundNode->Set(foundNodeNew->key);
	foundNode->value = foundNodeNew->value;

	TNode * parentOfSecondNode = foundNodeNew->parent;
	if(parentOfSecondNode->left == foundNodeNew){ // Родитель второго узла указывает на него налево
		//std::cout << "Flag1 ";
		if(isLeafTmp2){ // 1 случай
			//std::cout << "Leaf\n";
			parentOfSecondNode->left = foundNode;
		}
		else{
			if(isLeftForNodeTmp){ // 4.1
				//std::cout << "stage one\n";
				parentOfSecondNode->left = foundNodeNew->right;
				foundNodeNew->right->parent = parentOfSecondNode;
			}
			else{
				//std::cout << "stage two\n";
				parentOfSecondNode->left = foundNodeNew->left;
				foundNodeNew->left->parent = parentOfSecondNode;
			}

			if(isLeftForNodeTmp2){
				//std::cout << "stage three\n";
				foundNodeNew2->left = foundNode;
			}
			else{
				//std::cout << "stage four\n";
				foundNodeNew2->right = foundNode;
			}
		}
	}
	else{
		//std::cout << "Flag2 ";
		if(isLeafTmp2){
			//std::cout << "Leaf\n";
			parentOfSecondNode->right = foundNode;
		}
		else{
			if(isLeftForNodeTmp){ // 4.1
				//std::cout << "stage one\n";
				parentOfSecondNode->right = foundNodeNew->right;
				foundNodeNew->right->parent = parentOfSecondNode;
			}
			else{
				//std::cout << "stage two\n";
				parentOfSecondNode->right = foundNodeNew->left;
				foundNodeNew->left->parent = parentOfSecondNode;
			}

			if(isLeftForNodeTmp2){
				//std::cout << "stage three\n";
				foundNodeNew2->left = foundNode;
			}
			else{
				//std::cout << "stage four\n";
				foundNodeNew2->right = foundNode;
			}
		}
	}

	// if(isLeftForNodeTmp){ // left for second node
	// TNode * parentOfFoundNode = foundNodeNew->parent;
	// if(parentOfFoundNode->left == foundNodeNew){ // left from parent second node to second node
	// 	std::cout << "Flag11!";
	// 	if(isLeafTmp2){ // check for third node is leaf
	// 		std::cout << " Leaf!\n";
	// 		parentOfFoundNode->left = foundNode;
	// 	}
	// 	else{
	// 		std::cout << " not Leaf!\n";

	// 		if(isLeftForNodeTmp){
	// 			std::cout << " Kek1\n";
	// 			parentOfFoundNode->left = foundNodeNew->right;
	// 		}
	// 		else{
	// 			std::cout << " Kek2\n";
	// 			parentOfFoundNode->left = foundNodeNew->left;
	// 		}

	// 		if(foundNodeNew->right->ind > foundNodeNew->parent->ind){
	// 			foundNodeNew->right->parent = parentOfFoundNode;
	// 		}

	// 		if(isLeftForNodeTmp2){
	// 			foundNodeNew2->left = foundNode;
	// 		}
	// 		else{
	// 			foundNodeNew2->right = foundNode;
	// 		}
	// 	}
	// }
	// else{ // right from parent second node to second node
	// 	std::cout << "Flag12! ";
	// 	if(isLeafTmp2){ // check for third node is leaf
	// 		std::cout << " Leaf!\n";
	// 		parentOfFoundNode->right = foundNodeNew2;
	// 		foundNodeNew2->parent = parentOfFoundNode;
	// 	}
	// 	else{
	// 		std::cout << foundNodeNew->key;
	// 		std::cout << " not Leaf!\n";

	// 		if(isLeftForNodeTmp){
	// 			parentOfFoundNode->right = foundNodeNew->right;
	// 		}
	// 		else{
	// 			parentOfFoundNode->right = foundNodeNew->left;
	// 		}

	// 		if(foundNodeNew->right->ind > foundNodeNew->parent->ind){
	// 			foundNodeNew->right->parent = parentOfFoundNode;
	// 		}

	// 		if(isLeftForNodeTmp2){ // arrow of third node
	// 			foundNodeNew2->left = foundNode;
	// 		}
	// 		else{
	// 			foundNodeNew2->right = foundNode;
	// 		}	
	// 	}	
	// }
	// else{
	// 	TNode * parentOfFoundNode = foundNodeNew->parent;
	// 	if(parentOfFoundNode->left == foundNodeNew){ // left from parent second node to second node
	// 		if(isLeafTmp2){ // check for third node is leaf
	// 			parentOfFoundNode->left = foundNode;
	// 		}
	// 		else{
	// 			parentOfFoundNode->left = foundNodeNew->right;
	// 			if(foundNodeNew->right->ind > foundNodeNew->parent->ind){
	// 				foundNodeNew->right->parent = parentOfFoundNode;
	// 			}		
	// 		}
	// 	}
	// 	else{ // right from parent second node to second node
	// 		if(isLeafTmp2){ // check for third node is leaf
	// 			parentOfFoundNode->right = foundNode;
	// 		}
	// 		else{
	// 			parentOfFoundNode->right = foundNodeNew->right;
	// 			if(foundNodeNew->right->ind > foundNodeNew->parent->ind){
	// 				foundNodeNew->right->parent = parentOfFoundNode;
	// 			}	
	// 		}	
	// 	}
	// }
		// TNode * parentOfFoundNode = foundNodeNew->parent;
		// if(parentOfFoundNode->right == foundNodeNew){
		// 	std::cout << "Q1 ";
		// 	if(isLeafTmp2){
		// 		std::cout << "B1\n";
		// 		parentOfFoundNode->right = foundNodeNew->left;
		// 	}
		// 	else{
		// 		std::cout << "B2\n";
		// 		parentOfFoundNode->right = foundNodeNew->right;
		// 	}

		// 	if(parentOfFoundNode->ind < foundNodeNew->left->ind){
		// 		foundNodeNew->left->parent = parentOfFoundNode;
		// 	}
		// }
		// else{
		// 	std::cout << "Q2 ";
		// 	if(isLeafTmp2){
		// 		std::cout << "B1\n";
		// 		parentOfFoundNode->left = foundNodeNew->left;
		// 	}
		// 	else{
		// 		std::cout << "B2\n";
		// 		parentOfFoundNode->left = foundNodeNew->right;
		// 	}

		// 	if(parentOfFoundNode->ind < foundNodeNew->right->ind){
		// 		foundNodeNew->right->parent = parentOfFoundNode;
		// 	}
		// }
	// }
	// else{
	// 	TNode * parentOfFoundNode = foundNodeNew->parent;
	// 	if(parentOfFoundNode->right == foundNodeNew){
	// 		std::cout << "Q3 ";
	// 		if(isLeafTmp2){
	// 			std::cout << "B1\n";
	// 			parentOfFoundNode->right = foundNodeNew->right;
	// 		}
	// 		else{
	// 			std::cout << "B2\n";
	// 			parentOfFoundNode->right = foundNodeNew->left;
	// 		}

	// 		if(parentOfFoundNode->ind < foundNodeNew->left->ind){
	// 			foundNodeNew->left->parent = parentOfFoundNode;
	// 		}
	// 	}
	// 	else{
	// 		std::cout << "Q4 ";
	// 		if(isLeafTmp2){
	// 			std::cout << "B1\n";
	// 			parentOfFoundNode->left = foundNodeNew->right;
	// 		}
	// 		else{
	// 			std::cout << "B2\n";
	// 			parentOfFoundNode->left = foundNodeNew->left;
	// 		}
	// 	}
	// }

	// if(isLeftForNodeTmp2){
	// 	foundNodeNew2->left = foundNode;
	// }
	// else{
	// 	foundNodeNew2->right = foundNode;
	// }

	//std::cout << "Was -> " << foundNode->key;
	//std::cout << ", I deleting it-> " << foundNodeNew->key << '\n';
	std::cout << "OK\n";
	delete foundNodeNew;

	return startNode;
}

void TreeDelete(TNode * node) {
	if (!node) {
		return;
	}

	//std::cout << "Delete it: " << node->key << '\n';
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

void PrintTree(TNode * root, int space) {
	if (!root) {
		return;
	}

	std::cout << root->value << ".\t";

	for (int i = 0; i < space; ++i)
	{
		std::cout << '\t';
	}

	if(strlen(root->key) > 5){
		char * cKey = root->key;
		std::cout << cKey[0] << cKey[1] << cKey[2] << cKey[3] << cKey[4] << "...";
	}
	else{
		std::cout << root->key;
	}

	std::cout << " (" << root->ind << ", " << root->value << ", \"" << root->left->key << "\", ";
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
	if (root->left->ind > ind) {
		PrintTree(root->left, space + 1);
	}

	if (root->right != nullptr && root->right->ind > ind) {
		PrintTree(root->right, space + 1);
	}
}