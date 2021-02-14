#include "BM.hpp"

namespace bm {
	void ComplexRules(const std::string& pattern, std::unordered_map<char, std::vector<int> >& BadSymbol, std::unordered_map<std::string, int >& GoodSuffix) {
		int patternSize = pattern.size(), halfSize = patternSize >> 1;

		std::string curPattern = "";
		int curPatSz = 0;
		for (int i = patternSize - 1; i >= 0; --i)
		{
			char curChar = pattern[i];
			// Bad Symbol
			BadSymbol[curChar].push_back(i + 1);
			// Good Suffix
			if (i >= halfSize) {
				curPattern = curChar + curPattern;
				curPatSz++;

				int curIndexOfcurPattern = curPatSz - 1;
				for (int j = i - 1; j >= 0; --j) {
					if (curPattern[curIndexOfcurPattern] == pattern[j]) {
						if (curIndexOfcurPattern == 0) {
							GoodSuffix[curPattern] = i - j;
							break;
						}
						curIndexOfcurPattern--;
					}
					else {
						curIndexOfcurPattern = curPatSz - 1;
					}
				}
			}
		}
	}

	std::unordered_map<char, std::vector<int> > RulerBadSymbol(const std::string& pattern) {
		std::unordered_map<char, std::vector<int> > resultMap;

		int patternLength = pattern.length();

		for (int i = patternLength - 1; i >= 0; i--)
		{
			resultMap[pattern[i]].push_back(i + 1);

			//char curSymbol = pattern[i];
			/*std::unordered_map<char, std::vector<int> >::iterator itFind = resultMap.find(curSymbol);
			if (itFind == resultMap.end())
				resultMap[curSymbol] = { i + 1 };
			else
				itFind->second.push_back(i + 1);*/
		}

		return resultMap;
	}

	std::unordered_map<std::string, int> RulerGoodSuffix(const std::string& pattern) {
		std::unordered_map<std::string, int> result;
		
		std::string curPattern = "";

		int patSz = pattern.size(), curPatSz = 0;
		for (int i = patSz - 1; i >= patSz/2; --i) // abcdef yyycc
		{
			curPattern = pattern[i] + curPattern;
			curPatSz++;

			int curIndexOfcurPattern = curPatSz - 1;
			for (int j = i - 1; j >= 0; --j) {
				if (curPattern[curIndexOfcurPattern] == pattern[j]) {
					if (curIndexOfcurPattern == 0) {
						result[curPattern] = i - j;
						break;
					}
					curIndexOfcurPattern--;
				}
				else {
					curIndexOfcurPattern = curPatSz - 1;
				}
			}
		}

		return result;
	}
}