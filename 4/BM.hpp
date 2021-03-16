#pragma once
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>

namespace BM {
	// Additional functions
	std::vector<int> ZFunction(const std::vector<std::string>& pattern);

	// Parses pattern with bad symbol ruler
	std::unordered_map<std::string, std::vector<int> > RulerBadSymbol(const std::vector<std::string>& pattern);
	// Parses pattern with good suffix ruler
	std::pair<std::vector<int>, std::vector<int> > RulerGoodSuffix(const std::vector<std::string>& pattern);

	// Functions which find indexes from rules
	int FindBadSymbol(const std::unordered_map<std::string, std::vector<int> >& ruler, const std::string& word, const int index);
	int FindGoodSuffix(const std::pair<std::vector<int>, std::vector<int> >& ruler, const int index);
}
