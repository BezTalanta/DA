#pragma once
#include <vector>
#include <string>
//#include <sstream>
#include <iostream>

#include <map>
#include <unordered_map>
#include <iterator>

namespace bm {
	//std::vector<int> FindPattern(const std::string & pattern);
	std::map<char,int> FindPattern(const std::string& pattern);
	std::unordered_map<char, std::vector<int>> RulerBadSymbol(const std::string& pattern);
	std::map<char, int> RulerGoodSuffix(const std::string& pattern);
}