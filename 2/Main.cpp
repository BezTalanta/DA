#include <string>
#include <stdio.h>
#include "tree.h"
#include <time.h>

using ull = unsigned long long;

const int sizeOfChars = 256;
int globalCountOfNodes = 0;
/*
	a - 97 -> 1100001
	z - 122 -> 1111010
	A - 65 -> 1000001
	Z - 90 -> 1011010
*/

void GOBit(int a) {
	std::cout << a << " ->  ";
	int countOfBits = 5;
	for (int i = 0; i < countOfBits; i++)
	{
		if (a >> (countOfBits - 1 - i) & 1) {
			std::cout << "1";
		}
		else {
			std::cout << "0";
		}
	}
	std::cout << '\n';
}

void Test(bool & a) {
	a = true;
	return;
}

// 18446 74407 37095 51615
int main(int c, char * v[])
{	
	// std::ifstream file("txt.txt");
	// TNode * treeNew = Load(file);
	// PrintTree(treeNew,0);
	// return 0;
	time_t start = clock();
	setlocale(LC_ALL, "rus");
	/*for (int i = 97; i < 123; i++)
	{
		std::cout << (char)i << ": ";
		GOBit(i-96);
	}	*/

	/*char * cyka = new char[5];
	std::cin >> cyka;
	std::cout << cyka << '\n';
	return 0;*/

	/*bool v = false;
	Test(v);*/
	/*std::cout << v << '\n';
	return 0;*/
	//char t[256],t2[256];

	// WORKED

	//char * t = new char[256];
	//TNode *mainTree =  nullptr;
	////TNode * test = new TNode,* test2 = new TNode;
	//TNode * node;
	//while (std::cin >> t && t[0] != '\x4') {
	//	node = new TNode;
	//	node->key = t;
	//	mainTree = InsertNode(mainTree, node);
	//	t = new char[256];
	//}
	//delete[] t;
	//PrintTree(mainTree,1);
	//NodeDelete(mainTree);
	//return 0;

	TNode * tree = nullptr;
	char * command = new char[MAX_SIZE_OF_CHARS];
	while (std::cin >> command && command[0] != '\x4') {
		if (command[0] == '+') {
			std::cin >> command;
			for (int i = 0; i < strlen(command); i++)
			{
				command[i] = tolower(command[i]);
			}			

			ull in;
			std::cin >> in;
			TNode * newNode = new TNode;
			newNode->value = in;
			newNode->key = command;
			tree = InsertNode(tree, newNode);
		}
		else if (command[0] == '$') {
			PrintTree(tree, 0);
			delete[] command;
		}
		else if (command[0] == '-') {
			std::cin >> command;
			for (int i = 0; i < strlen(command); i++)
			{
				command[i] = tolower(command[i]);
			}
			tree = DeleteNode(tree, command);

			delete[] command;
		}
		else if(command[0] == '!'){
			delete[] command;
			command = new char[MAX_SIZE_OF_CHARS];

			std::cin >> command;
			if(strcmp(command,"Save") == 0){
				delete[] command;
				command = new char[MAX_SIZE_OF_CHARS];				
				std::cin >> command;

				std::ofstream file(command);
				if(!file.is_open()){
					std::cout << "Error: file didn't open\n";
				}
				else{
					Save(tree,file);
					file.close();
				}
				//std::cout << "\tAll OK\n";
			}
			else if(strcmp(command,"Load") == 0){
				delete[] command;
				command = new char[MAX_SIZE_OF_CHARS];				
				std::cin >> command;

				std::ifstream file(command);
				if(!file.is_open()){
					std::cout << "Error: file didn't open\n";
				}
				else{
					TreeDelete(tree);
					tree = Load(file);
					file.close();
				}
			}
			delete[] command;
		}
		else {
			for (int i = 0; i < strlen(command); i++)
			{
				command[i] = tolower(command[i]);
			}
			TNode * foundNode = SearchNode(tree, command);
			if (foundNode && strcmp(foundNode->key,command) == 0) {
				std::cout << "OK: " << foundNode->value << '\n';
			}
			else {
				std::cout << "NoSuchWord\n";
			}
			delete[] command;
		}

		command = new char[MAX_SIZE_OF_CHARS];
	}
	delete[] command;

	TreeDelete(tree);

	time_t end = clock();
	std::cout << "Your work time: " << (double)(end-start)/CLOCKS_PER_SEC << '\n';
	return 0;
}