#pragma once
#include <vector>
#include <string>
#include <iostream>

#include <unordered_map>
#include <iterator>

namespace bm {
	std::unordered_map<char, std::vector<int> > RulerBadSymbol(const std::string& pattern);
	std::unordered_map<std::string, int > RulerGoodSuffix(const std::string& pattern);
	void ComplexRules(const std::string& pattern, std::unordered_map<char, std::vector<int> >& BadSymbol, std::unordered_map<std::string, int >& GoodSuffix);
}

/*
cat dog cat dog bird
CAT dog CaT Dog Cat DOG bird CAT
dog cat dog bird
*/