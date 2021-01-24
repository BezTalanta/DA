#include "BM.hpp"

namespace bm {
	std::map<char, int> FindPattern(const std::string& pattern){ // O(log n)
		std::map<char, int> resultPattern;

		int patternLength = pattern.length();
		for (int i = patternLength - 1; i >= 0; i--)
		{
			char curSymbolOfStartPatter = pattern[i];
			// Find symbol of start pattern in result pattern
			std::map<char, int>::iterator check = resultPattern.find(curSymbolOfStartPatter);
			if (check == resultPattern.end()) {
				resultPattern[curSymbolOfStartPatter] = i+1;
			}
		}

		return resultPattern;
	}

	std::unordered_map<char, std::vector<int>> RulerBadSymbol(const std::string& pattern) {
		std::unordered_map<char, std::vector<int>> resultMap;
		int patternLength = pattern.length();
		for (int i = patternLength - 1; i >= 0; i--)
		{
			char curSymbol = pattern[i];
			std::unordered_map<char, std::vector<int>>::iterator itFind = resultMap.find(curSymbol);
			if (itFind == resultMap.end()) {
				std::vector<int> vct;
				vct.push_back(i+1);
				resultMap[curSymbol] = vct;
			}
			else {
				std::vector<int> vct = itFind->second;
				vct.push_back(i+1);
				itFind->second = vct;
			}
		}

		return resultMap;
	}
}