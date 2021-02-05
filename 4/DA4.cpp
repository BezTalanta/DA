#include "BM.hpp"

// Get word's indexes from text
std::vector<int> WordsInd(std::string& text);
// Get patternS's chars to lower case
std::string GetRightLine(std::string& patternS);

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL), std::cout.tie(NULL);

    // Get pattern and change to normal view
    std::string patternS;
    std::getline(std::cin,patternS);
    if (patternS[0] == '\x4' || patternS == "") return 1;

    patternS = GetRightLine(patternS);
    int patternLen = patternS.length();

    // Pattern with Bad symbol rule
    std::unordered_map<char, std::vector<int> > pattern = bm::RulerBadSymbol(patternS);

    std::string text = "", word;
    int sumIndexesLines = 0;
    std::vector<std::vector<int>> indWords; // Indexes of words from lines
    std::vector<int> indLines; // Indexes of lines

    // Read user in
    while (std::getline(std::cin, word) && word != "\x4") {
        word = GetRightLine(word);
        std::vector<int> tmp = WordsInd(word); // Get indexes of spaces
        indWords.push_back(tmp); // Add indexes vector
        int curLen = word.length();
        if(word != ""){
            indLines.push_back(curLen + sumIndexesLines);
            sumIndexesLines += curLen + 1; // Add one space in the end of the line
            text += word + " ";
        }
        else{
            indLines.push_back(0);
        }
    } 
    int textLen = text.length();
    if (!textLen) return 0;

    text.erase(text.end() - 1); // Delete last space

    // Check pattern to text    
    std::vector<int> resultF, resultS;

    int currenPositionInText = patternLen;
    while (currenPositionInText <= textLen) {
        for (int i = 0; i < patternLen; i++)
        {
            char chFromText = text[currenPositionInText - i - 1], chFromPattern = patternS[patternLen - i - 1];
            if (chFromPattern != chFromText) {
                std::unordered_map<char, std::vector<int> >::iterator itFind = pattern.find(chFromText);

                int patI = patternLen - i;
                if (itFind == pattern.end()) {
                    currenPositionInText += patI; // maybe wrong
                    break;
                }
                
                int offset = 0;
                for (const int& charPositions : itFind->second) {
                    if (charPositions < patI) {
                        offset = patI - charPositions;
                        break;
                    }
                }

                if (offset != 0) currenPositionInText += offset;
                else currenPositionInText++;

                break;
            }
            else if (i == patternLen - 1) { // Found match                
                int position = currenPositionInText - patternLen;
                int foundIndLn = 1, offset = 0;
                for (int checkLines : indLines) {
                    if (position < checkLines) break;
                    foundIndLn++;
                    if(checkLines != 0) offset = checkLines;
                }

                int positionInLine = position - offset - 1;
                std::vector<int> curIndWords = indWords[foundIndLn - 1];
                int resultIndOfWord = 1;
                for (int tmp : curIndWords) {
                    if (positionInLine < tmp) break;
                    resultIndOfWord++;
                }
                                
                resultF.push_back(foundIndLn);
                resultS.push_back(resultIndOfWord);

                currenPositionInText++;
            }
        }
    }

    //std::cout << resultSize << '\n';
    for (int i = 0; i < resultF.size(); ++i) {
        std::cout << resultF[i] << ", " << resultS[i] << '\n';
    }

    return 0;
}

// Get patternS's chars to lower case
std::string GetRightLine(std::string& patternS) {
    std::string res = "";

    bool isSpaceFound = false, firstSymbolFound = false;
    for (int i = 0; i < patternS.length(); i++)
    {
        if(patternS[i] >= 'A' && patternS[i] <= 'Z'){
            if(isSpaceFound) res += ' ';
            res += patternS[i] + 32;
            isSpaceFound = false;
            firstSymbolFound = true;
        }
        else if(patternS[i] == ' ' && firstSymbolFound) isSpaceFound = true;
        else if(patternS[i] != ' '){
            if(isSpaceFound) res += ' ';
            res += patternS[i];
            firstSymbolFound = true;
            isSpaceFound = false;
        }
    }
    return res;
}

// Get word's indexes from text
std::vector<int> WordsInd(std::string& text) {
    std::vector<int> result;

    int textLen = text.length();
    for (int i = 0; i < textLen; i++)
    {
        if (text[i] == ' ') result.push_back(i);
    }

    return result;
}