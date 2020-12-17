#include "tree.hpp"

namespace trie{
const int USE_FOR_BYTES = 126;
const int BYTES_OF_ONE_CHAR = 5;

int & GetMin(int & a, int & b) {
	if (a > b) {
		return b;
	}
	return a;
}

int GetDifference(trie::TNode * a, trie::TNode * b, bool & isOneForNewNode) {
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

trie::TNode * SearchNode(trie::TNode * needToFoundOwner,bool & isLeaf, bool & isLeftForFoundNode) {
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

trie::TNode * SearchNode(trie::TNode * startNode, char * key) {
	if (!startNode) {
		return nullptr;
	}

	trie::TNode * curNode = startNode->left, * prevNode = startNode;
	int prevInd = 0, curInd = curNode->ind, maxInd = strlen(key) * BYTES_OF_ONE_CHAR;
	while (curInd > prevInd) {
		int indOfWord = curInd / BYTES_OF_ONE_CHAR, indOfLetter = curInd % BYTES_OF_ONE_CHAR;
		if (indOfLetter == 0) indOfWord--,indOfLetter = BYTES_OF_ONE_CHAR;

		if (curInd > maxInd) {
			key[indOfWord] = '\0';
		}

		if ((key[indOfWord] >> (BYTES_OF_ONE_CHAR - indOfLetter)) & 1) {
			prevNode = curNode;
			curNode = curNode->right;
		}
		else {
			prevNode = curNode;
			curNode = curNode->left;
		}

		prevInd = curInd;
		curInd = curNode->ind;
	}

	return curNode;
}

trie::TNode * InsertNode(trie::TNode * startNode, trie::TNode * newNode, bool needOK) {
	if (!startNode) {
		newNode->left = newNode;
		newNode->right = nullptr;
		newNode->parent = nullptr;
		newNode->ind = 0;
		if(needOK){
			std::cout << "OK\n";
		}
		globalCountOfNodes++;
		return newNode;
	}

	trie::TNode * foundNode = trie::SearchNode(startNode,newNode->key);
	if (*foundNode == newNode) {
		delete newNode;
		std::cout << "Exist\n";
		return startNode;
	}

	// Bool in order know the direction of the right arrow of the newNode
	bool isOneForNewNode = false;
	int dif = GetDifference(foundNode,newNode,isOneForNewNode);
	//std::cout << "Dif ind: " << dif << ' ';
	newNode->ind = dif;

	trie::TNode * curN = startNode->left, * prevN = startNode;
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

	if(needOK){
		std::cout << "OK\n";
	}
	globalCountOfNodes++;
	return startNode;
}

trie::TNode * DeleteNode(trie::TNode * startNode, char * keyIn) {
	if (!startNode) {
		std::cout << "NoSuchWord\n";
		return startNode;
	}
	
	if (startNode->left == startNode) {
		delete startNode;
		std::cout << "OK\n";
		trie::globalCountOfNodes--;
		return nullptr;
	}

	trie::TNode * foundNode = trie::SearchNode(startNode,keyIn);
	if (strcmp(foundNode->key, keyIn) != 0) {
		std::cout << "NoSuchWord\n";
		return startNode;
	}

	bool isLeafTmp = false, isLeftForNodeTmp = false;
	trie::TNode * foundNodeNew = SearchNode(foundNode, isLeafTmp, isLeftForNodeTmp);

	if(isLeafTmp){ // Когда удаляемый элемент - лист
		trie::TNode * parentOfFoundNode = foundNode->parent;
		if(parentOfFoundNode->left == foundNode){
			if(isLeftForNodeTmp){
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
				parentOfFoundNode->right = foundNode->right;
			}
			else{
				parentOfFoundNode->right = foundNode->left;
			}

			if(parentOfFoundNode->ind < parentOfFoundNode->right->ind){
				parentOfFoundNode->right->parent = parentOfFoundNode;
			}
		}

		trie::globalCountOfNodes--;
		std::cout << "OK\n";
		delete foundNode;
		return startNode;
	}

	bool isLeafTmp2 = false, isLeftForNodeTmp2 = false;
	trie::TNode * foundNodeNew2 = SearchNode(foundNodeNew, isLeafTmp2, isLeftForNodeTmp2);

	// Меняем значения первого нода на значения второго
	foundNode->Set(foundNodeNew->key);
	foundNode->value = foundNodeNew->value;

	trie::TNode * parentOfSecondNode = foundNodeNew->parent;
	if(parentOfSecondNode->left == foundNodeNew){ // Родитель второго узла указывает на него налево
		//std::cout << "Flag1 ";
		if(isLeafTmp2){ // 1 случай
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

	globalCountOfNodes--;
	std::cout << "OK\n";
	delete foundNodeNew;

	return startNode;
}

void TreeDelete(trie::TNode * node) {
	if (!node) {
		return;
	}

	int nodeInd = node->ind;
	if (node->left->ind > nodeInd) {
		trie::TreeDelete(node->left);
	}

	if (node->right != nullptr && node->right->ind > nodeInd) {
		trie::TreeDelete(node->right);
	}

	delete node;
}

// aa ahb ahc ap apr
// aa ao ag ae af ad
// abp abpp abppp

void PrintTree(trie::TNode * root, int space) {
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
		trie::PrintTree(root->left, space + 1);
	}

	if (root->right != nullptr && root->right->ind > ind) {
		trie::PrintTree(root->right, space + 1);
	}
}

void Save(trie::TNode * startNode, std::ofstream & file){
	if(!startNode) { std::cout << "Error: tree is empty!\n";return; }

	int curInd = startNode->ind;
	file << startNode->key << ' ' << startNode->ind << ' ';
	file << startNode->value << '\n';

	if(startNode->left->ind > curInd){
		trie::Save(startNode->left,file);
	}

	if(startNode->right != nullptr && startNode->right->ind > curInd){
		trie::Save(startNode->right,file);
	}
}

trie::TNode * Load(std::ifstream & file){
	trie::TNode * tree = nullptr;
	char * line = new char[1000];
	while(file.getline(line,1000)){
		trie::TNode * newNode = new trie::TNode;
		char * kek = new char[MAX_SIZE_OF_CHARS] {'\0'};
		int indOfKek = 0,state = -1;
		for (int i = 0; i < strlen(line); ++i)
		{
			if(line[i] == ' ' || line[i] == '\n'){
				state++;
				indOfKek = 0;
			}
			else{
				kek[indOfKek] = line[i];
				indOfKek++;
				continue;
			}

			if(state == 0){
				newNode->key = kek;
			}
			else if(state == 1){
				newNode->ind = 0;
				for (int i = 0; i < strlen(kek); ++i)
				{
					newNode->ind *= 10;
					newNode->ind += kek[i] - '0';
				}
				delete[] kek;
			}
			
			kek = new char[MAX_SIZE_OF_CHARS] {'\0'};
		}

		newNode->value = 0;
		for (int i = 0; i < strlen(kek); ++i)
		{
			newNode->value *= 10;
			newNode->value += kek[i] - '0';
		}
		delete[] kek;
		tree = trie::InsertNode(tree, newNode, false);
	}

	delete[] line;
	return tree;
}
}