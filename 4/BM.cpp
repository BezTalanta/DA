#include "BM.hpp"

namespace bm {
	std::unordered_map<char, std::vector<int> > RulerBadSymbol(const std::string& pattern) {
		std::unordered_map<char, std::vector<int> > resultMap;

		int patternLength = pattern.length();

		for (int i = patternLength - 1; i >= 0; i--)
		{
			char curSymbol = pattern[i];

			std::unordered_map<char, std::vector<int> >::iterator itFind = resultMap.find(curSymbol);
			if (itFind == resultMap.end())
				resultMap[curSymbol] = { i + 1 };
			else
				itFind->second.push_back(i + 1);
		}

		return resultMap;
	}

	std::unordered_map<char, std::vector<int> > RulerGoodSuffix(const std::string& pattern) {
		std::unordered_map<char, std::vector<int> > result;
		
		std::string curPattern = "";

		for (int i = pattern.size() - 1; i >= 0; --i)
		{
			curPattern += pattern[i];
			
			std::vector<int> curVct;
			for (int j = i - 1; j >= 0; --j) {

			}
		}

		return result;
	}
}