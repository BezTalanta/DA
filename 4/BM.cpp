#include "BM.hpp"

namespace BM {
	std::vector<int> ZFunction(const std::vector<std::string>& pattern) {
        std::vector<int> result(pattern.size(), 0);
        for (int i = 1, l = 0, r = 0; i < pattern.size(); i++) {
            if (i <= r)
                result[i] = std::min(r - i + 1, result[i - l]);

            while (i + result[i] < pattern.size() &&
                pattern[pattern.size() - 1 - result[i]] ==
                pattern[pattern.size() - 1 - (i + result[i])])
                ++result[i];
            if (i + result[i] - 1 > r)
                l = i, r = i + result[i] - 1;
        }
        return result;
	}

	std::unordered_map<std::string, std::vector<int> > RulerBadSymbol(const std::vector<std::string>& pattern) {
		std::unordered_map<std::string, std::vector<int> > resultMap;
		for (int i = 0; i < pattern.size(); ++i) {
			resultMap[pattern[i]].push_back(i + 1);
		}
		return resultMap;
	}

    std::pair<std::vector<int>, std::vector<int> > RulerGoodSuffix(const std::vector<std::string>& pattern) {
        std::vector<int> zf = ZFunction(pattern);
        std::vector<int> nf(zf.rbegin(), zf.rend());

        int prevNum = 0;
        std::vector<int> L(pattern.size(), 0), l(pattern.size(), 0);
        for (int i = 1; i <= nf.size(); ++i) {
            // For L
            if (nf[i - 1] != 0) {
                L[pattern.size() - nf[i - 1]] = i;
            }
            //

            // For l'
            int j = nf.size() - (nf.size() - i + 1) + 1;
            if (j == nf[j - 1])
                prevNum = j;
            l[nf.size() - i] = prevNum;
            // 
        }

        return {L, l};
    }

    int FindBadSymbol(const std::unordered_map<std::string, std::vector<int> >& ruler, const std::string& word, const int index) {
        std::unordered_map<std::string, std::vector<int> >::const_iterator itFind = ruler.find(word);
        if (itFind == ruler.end())
            return 0;

        int prevNum = 0;
        for (const int& item : ruler.at(word)) {
            if (item < index)
                prevNum = item;
            else
                break;
        }

        if (!prevNum)
            return 0;
        return index - prevNum;
    }

    int FindGoodSuffix(const std::pair<std::vector<int>, std::vector<int> >& ruler, const int index) {
        if (index >= ruler.first.size())
            return 0;
        if (ruler.first[index] != 0)
            return ruler.first.size() - ruler.first[index];
        return ruler.second.size() - ruler.second[index];
    }
}

/*
C C T T T T G C
G C T T C T G C T A C C T T T T G C G C G C G C G C G G A A
1, 11

G T A G C G G C G
G T T A T A G C T G A T C G C G G C G T A G C G G C G A A
1, 19

cat dog cat dog bird
CAT dog CaT Dog Cat DOG bird CAT
dog cat dog bird
1, 3
1, 8
*/
