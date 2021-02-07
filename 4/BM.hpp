#pragma once
#include <vector>
#include <string>
#include <iostream>

#include <unordered_map>
#include <iterator>

namespace bm {
	std::unordered_map<char, std::vector<int> > RulerBadSymbol(const std::string& pattern);
	std::unordered_map<char, std::vector<int> > RulerGoodSuffix(const std::string& pattern);
}