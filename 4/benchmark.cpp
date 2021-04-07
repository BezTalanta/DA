#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include <chrono>

void GetLower(std::string& in){
	for(char& ch: in)
		ch = tolower(ch);
}

int main(){
	auto start = std::chrono::steady_clock::now();
	std::string pattern = " a ", fullText, currentText;
	while(std::cin >> currentText){
		GetLower(currentText);
		fullText += currentText + ' ';
	}

	std::vector<int> result;
	int curInt = 0, count = 0;
	while((curInt = fullText.find(pattern, curInt + 1)) != fullText.npos){
		++count;
		result.push_back(curInt);
	}

	auto finish = std::chrono::steady_clock::now();
	std::cout << "Work time: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << "ms\n";
	std::cout << "Result count: " << count << '\n';
	for(const int& item: result)
		std::cout << item << ' ';
	std::cout << '\n';
}