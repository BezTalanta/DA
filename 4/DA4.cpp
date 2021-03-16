#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include "BM.hpp"

// Get line of text from input and convert upper case chars to lower
bool GetLine(std::vector<std::string>& vct);
// Is word has only from a to z and numbers
bool IsWordCorrect(const std::string& probablyWord);

int main()
{
	std::vector<std::string> pattern;
	if (!GetLine(pattern)) // If pattern is empty
		return 0;

	std::unordered_map<std::string, std::vector<int> > patternBadSymbol = BM::RulerBadSymbol(pattern);
	std::pair<std::vector<int>, std::vector<int> > patternGoodSuffix = BM::RulerGoodSuffix(pattern);	

	// std::string is word
	// std::pair first is line's index in text
	// std::pair second is word's index in line
	std::vector<std::pair<std::string, std::pair<int, int> > > text;

	// Text reading
	int currentLine = 1, currentWord = 1;
	std::vector<std::string> readLine;
	while (GetLine(readLine)) {
		for (const std::string& word : readLine) {
			//if (!IsWordCorrect(word)) // O(n), n - size of word
			//	continue;
			text.push_back({ word, {currentLine, currentWord} });
			++currentWord;
		}

		++currentLine;
		currentWord = 1;
		readLine.clear();
	}

	std::vector<std::pair<int, int> > result;
	int leftPatternPosition = 0;
	while (leftPatternPosition + pattern.size() <= text.size()) {
		for (int i = pattern.size() - 1; i >= 0; --i) {
			std::string& currentWord = text[leftPatternPosition + i].first;
			//std::cout << "DEBUG: " << currentWord << ' ' << pattern[i] << '\n';
			if (currentWord != pattern[i]) {
				int badRuler = BM::FindBadSymbol(patternBadSymbol, currentWord, i + 1);
				int goodRuler = BM::FindGoodSuffix(patternGoodSuffix, i + 1);
				if (badRuler == 0 && goodRuler == 0) {
					++leftPatternPosition;
					//std::cout << "I used one ruler with num: 1\n";
				}
				else if (badRuler > goodRuler) {
					leftPatternPosition += badRuler;
					//std::cout << "I used bad ruler with num: " << badRuler << '\n';
				}
				else {
					leftPatternPosition += goodRuler;
					//std::cout << "I used good ruler with num: " << goodRuler << '\n';
				}
				break;
			}
			else if (i == 0) {
				result.push_back(text[leftPatternPosition + i].second);
				int goodRuler = BM::FindGoodSuffix(patternGoodSuffix, 0);
				if (goodRuler == 0) {
					++leftPatternPosition;
					//std::cout << "I used one ruler with num: 1\n";
				}
				else {
					leftPatternPosition += goodRuler;
					//std::cout << "I used good ruler with num: " << goodRuler << '\n';
				}
			}
		}
	}
	
	for (const auto& item : result)
		std::cout << item.first << ", " << item.second << '\n';
	return 0;
}

bool GetLine(std::vector<std::string>& vct) {
	std::string currentString;
	if (!std::getline(std::cin, currentString) || currentString == "\x4")
		return false;

	std::stringstream ss(currentString);
	std::string wordFromLine;
	while (ss >> wordFromLine) {
		// Converts letters to lowercase
		for (char& ch : wordFromLine)
			ch = tolower(ch);

		vct.push_back(wordFromLine);
	}

	return true;
}

bool IsWordCorrect(const std::string& probablyWord) {
	for (const char& ch : probablyWord)
		if (!std::isalpha(ch))
			return false;
	return true;
}
