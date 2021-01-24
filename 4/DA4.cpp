#include "BM.hpp"

// Get word's indexes from text
std::vector<int> WordsInd(std::string& text);
// Get patternS's chars to lower case
void GetLower(std::string& patternS);

int main()
{
    // Get pattern and change to normal view
    std::string patternS;
    std::getline(std::cin,patternS);
    if (patternS[0] == '\x4') return 1;

    GetLower(patternS);
    int patternLen = patternS.length();

    std::cout << patternS << '\n';
    for (int i = 0; i < patternLen; i++)
    {
        std::cout << i + 1;
    }
    std::cout << '\n';

    std::unordered_map<char, std::vector<int>> pattern = bm::RulerBadSymbol(patternS);
    
    /*for (const auto& tmp : pattern) {
        std::cout << tmp.first << ' ';
        std::vector<int> tmpV = tmp.second;
        for (int i : tmpV) {
            std::cout << '[' << i << "] ";
        }
        std::cout << '\n';
    }*/

    std::string text = "", word;
    int textLen, sumIndexesLines = 0;
    std::vector<std::vector<int>> indWords;
    std::vector<int> indLines;
    while (std::getline(std::cin, word) && word != "\x4") {
        // Get space indexes from line
        GetLower(word);
        std::vector<int> tmp = WordsInd(word);

        indWords.push_back(tmp);
        int curLen = word.length();
        indLines.push_back(curLen + sumIndexesLines);
        sumIndexesLines += curLen;
        text += word + " ";
    }    
    textLen = text.length();
    if (!textLen) return 0;
    text.erase(text.end() - 1);

    // Check pattern to text    
    std::vector<int> resultF, resultS;

    int currenPositionInText = patternLen;
    while (currenPositionInText <= textLen) {
        for (int i = 0; i < patternLen; i++)
        {
            char chFromText = text[currenPositionInText - i - 1], chFromPattern = patternS[patternLen - i - 1];
            if (chFromPattern != chFromText) {
                std::unordered_map<char, std::vector<int>>::iterator itFind = pattern.find(chFromText);
                if (itFind == pattern.end()) {
                    currenPositionInText += patternLen - i; // maybe wrong
                    break;
                }
                
                int offset = 0, patI = patternLen - i;
                for (const int& charPositions : itFind->second) {
                    if (charPositions < patI) {
                        offset = patI - charPositions;
                        break;
                    }
                }

                if (offset != 0) {
                    currenPositionInText += offset;
                }
                else {
                    currenPositionInText++;
                }
                break;
            }
            else if (i == patternLen - 1) { // Found match                
                int currentLine = 0, position = currenPositionInText - patternLen;
                int foundIndLn = 1, offset = 0;
                for (int checkLines : indLines) {
                    if (position <= checkLines) break;
                    foundIndLn++;
                    offset = checkLines;
                }
                
                int positionInLine = position - offset - 1;
                std::vector<int> curIndWords = indWords[foundIndLn - 1];
                int sizeOfWords = curIndWords.size(), resultIndOfWord = 1;
                for (int tmp : curIndWords) {
                    if (positionInLine < tmp) break;
                    resultIndOfWord++;
                }
                                
                int resSize = resultF.size();
                resultF.push_back(foundIndLn);
                resultS.push_back(resultIndOfWord);

                currenPositionInText++;
            }
        }
    }

    int resultSize = resultF.size();
    for (int i = 0; i < resultSize; ++i) {
        std::cout << resultF[i] << ", " << resultS[i] << '\n';
    }

    return 0;
}

// Get patternS's chars to lower case 32
void GetLower(std::string& patternS) {
    int patLen = patternS.length();

    for (int i = 0; i < patLen; i++)
    {
        if (patternS[i] < 'a' && patternS[i] != ' ') patternS[i] += 32;
    }
}

// Get word's indexes from text
std::vector<int> WordsInd(std::string& text) {
    std::vector<int> result;

    int textLen = text.length();
    for (int i = 0; i < textLen; i++)
    {
        if (text[i] == ' ') {
            result.push_back(i);
        }
    }

    return result;
}

/*
cat dog cat dog bird
CAT dog CaT Dog Cat DOG bird CAT dog cat dog bird
*/

/*
    Plan:

    1) Get right pattern with spaces
    2) Get full text and data
*/