#include <iostream>
#include <string>
#include <stdio.h>
#include "tree.h"

using ull = unsigned long long;

const int sizeOfChars = 256;

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

int main()
{	
	setlocale(LC_ALL, "rus");
	/*for (int i = 97; i < 123; i++)
	{
		std::cout << (char)i << ": ";
		GOBit(i-96);
	}	*/
	/*bool v = false;
	Test(v);
	std::cout << v << '\n';
	return 0;*/
	char t[256],t2[256];
	std::cin >> t;
	TNode *tree2 =  nullptr;
	TNode * test = new TNode,* test2 = new TNode;
	test->key = t;
	test->sizeOfKey = strlen(t);

	std::cin >> t2;
	test2->key = t2;
	test2->sizeOfKey = strlen(t2);
	/*bool isTest = (*test2 == test);*/
	tree2 = AddNode(tree2, test);
	tree2 = AddNode(tree2, test2);
	return 0;
	TNode * tree = nullptr;
	char command[sizeOfChars] = "";
	while (std::cin >> command) {
		if (command[0] == '+') {
			std::cin >> command;	
			for (int i = 0; i < strlen(command); i++)
			{
				command[i] = tolower(command[i]);
			}			

			/*ull in;
			std::cin >> in;*/
		}
		else if (command[0] == 'q') {
			std::cin >> command;
			int converted = (int)command;
			std::cout << converted << '\n';
		}
	}
	return 0;
}