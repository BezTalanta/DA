#include <string>
#include <stdio.h>
#include "tree.hpp"
#include <time.h>

int main(int c, char * v[])
{
	std::ios_base::sync_with_stdio(false);

	time_t start = clock();
	setlocale(LC_ALL, "rus");

	trie::TNode * tree = 0;
	char * command = new char[MAX_SIZE_OF_CHARS+1];
	while (std::cin >> command && command[0] != '\x4') {
		if (command[0] == '+') {
			std::cin >> command;
			int len = strlen(command);
			for (int i = 0; i < len; i++)
			{
				command[i] = tolower(command[i]);
			}			

			ull in;
			std::cin >> in;
			trie::TNode * newNode = new trie::TNode;
			newNode->value = in;
			newNode->key = command;
			tree = trie::InsertNode(tree, newNode);
		}
		else if (command[0] == '$') {
			trie::PrintTree(tree, 0);
			delete[] command;
		}
		else if (command[0] == '-') {
			std::cin >> command;
			for (int i = 0; i < strlen(command); i++)
			{
				command[i] = tolower(command[i]);
			}
			tree = trie::DeleteNode(tree, command);

			delete[] command;
		}
		else if(command[0] == '!'){
			delete[] command;
			command = new char[MAX_SIZE_OF_CHARS+1];

			std::cin >> command;
			if(strcmp(command,"Save") == 0){
				delete[] command;
				command = new char[MAX_SIZE_OF_CHARS+1];				
				std::cin >> command;

				std::ofstream file(command);
				if(!file.is_open()){
					std::cout << "ERROR: file didn't open\n";
				}
				else{
					trie::Save(tree,file);
					file.close();
				}
			}
			else if(strcmp(command,"Load") == 0){
				delete[] command;
				command = new char[MAX_SIZE_OF_CHARS+1];				
				std::cin >> command;

				std::ifstream file(command);
				if(!file.is_open()){
					std::cout << "ERROR: file didn't open\n";
				}
				else{
					trie::TreeDelete(tree);
					tree = trie::Load(file);
					file.close();
					std::cout << "OK\n";
				}
			}
			delete[] command;
		}
		else {
			for (int i = 0; i < strlen(command); i++)
			{
				command[i] = tolower(command[i]);
			}
			trie::TNode * foundNode = trie::SearchNode(tree, command);
			if (foundNode && strcmp(foundNode->key,command) == 0) {
				std::cout << "OK: " << foundNode->value << '\n';
			}
			else {
				std::cout << "NoSuchWord\n";
			}
			delete[] command;
		}

		command = new char[MAX_SIZE_OF_CHARS+1];
	}
	delete[] command;

	trie::TreeDelete(tree);

	time_t end = clock();
	std::cout << "Your work time: " << (double)(end-start)/CLOCKS_PER_SEC << '\n';
	return 0;
}
