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
    std::getline(std::cin, patternS);
    if (patternS[0] == '\x4' || patternS == "") return 0;

    patternS = GetRightLine(patternS);
    int patternLen = patternS.length();

    // Pattern with Bad symbol rule
    std::unordered_map<char, std::vector<int> > ruleBadSymbol;
    // Pattern with Good Suffix rule
    std::unordered_map<std::string, int > ruleGoodSuffix;
    bm::ComplexRules(patternS, ruleBadSymbol, ruleGoodSuffix);
    //return 0;

    std::string text = "";                  // All text
    std::vector<std::vector<int>> indWords; // Line's vector which contains indexes of words
    std::vector<int> indLines;              // Vector contains indexes end of each line

    // Read user in
    int sumIndexesLines = 0;
    std::string word;
    while (std::getline(std::cin, word) && word != "\x4") {
        word = GetRightLine(word); // Delete multiply spaces and change upper-case letter to lower-case
        std::vector<int> tmp = WordsInd(word); // Get indexes of spaces
        indWords.push_back(tmp); // Add indexes vector
        int curLen = word.length();
        if (word != "") {
            indLines.push_back(curLen + sumIndexesLines);
            sumIndexesLines += curLen + 1; // Add one space in the end of the line
            text += word + " ";
        }
        else
            indLines.push_back(0); // If we have empty line
    }
    text.erase(text.end() - 1); // Delete last space

    int textLen = text.length();
    if (!textLen) return 0;
    //

    //std::cout << text << '\n';

    // Check pattern to text    
    std::vector<std::pair<int, int> > result;

    int currenPositionInText = patternLen;
    while (currenPositionInText <= textLen) {      
        std::string currentSuffix = "";
        for (int i = 0; i < patternLen; i++)
        {           
            char chFromText = text[currenPositionInText - i - 1], chFromPattern = patternS[patternLen - i - 1];            
            if (chFromPattern != chFromText) {
                std::unordered_map<char, std::vector<int> >::iterator itFind = ruleBadSymbol.find(chFromText);
                std::unordered_map<std::string, int >::iterator itFind2 = ruleGoodSuffix.find(currentSuffix);
               
                int offsetBad = 0, offsetGood = 0;

                int patI = patternLen - i;
                if (itFind != ruleBadSymbol.end()) {
                    for (const int& charPositions : itFind->second) {
                        if (charPositions < patI) {
                            offsetBad = patI - charPositions;
                            break;
                        }
                    }
                }

                if (itFind2 != ruleGoodSuffix.end())
                    offsetGood = itFind2->second;

                if (offsetBad == 0 && offsetGood == 0) {
                    std::cout << "One ruler past: " << currenPositionInText << ' ';
                    ++currenPositionInText;
                    std::cout << currenPositionInText << '\n';
                }
                else if (offsetBad > offsetGood) {
                    std::cout << "Bad ruler past: " << currenPositionInText << ' ';
                    currenPositionInText += offsetBad;
                    std::cout << currenPositionInText << '\n';
                }
                else {
                    std::cout << "Good ruler past: " << currenPositionInText << ' ';
                    currenPositionInText += offsetGood;                   
                    std::cout << currenPositionInText << '\n';
                }                

                break;
            }
            else if (i == patternLen - 1) { // Found match                
                int position = currenPositionInText - patternLen;
                int resultIndLine = 1, offset = 0;
                for (const int& checkLines : indLines) {
                    if (position < checkLines) break;
                    resultIndLine++;
                    if (checkLines != 0) offset = checkLines;
                }

                int positionInLine = position - offset - 1;
                std::vector<int> curIndWords = indWords[resultIndLine - 1];
                int resultIndOfWord = 1;
                for (const int& checkWords : curIndWords) {
                    if (positionInLine < checkWords) break;
                    resultIndOfWord++;
                }           

                result.push_back({ resultIndLine, resultIndOfWord});

                currenPositionInText++;
            }
            currentSuffix = chFromPattern + currentSuffix;
        }
    }    

    for (const std::pair<int, int>& pr : result)
        std::cout << pr.first << ", " << pr.second << '\n';

    return 0;
}

// Get patternS's chars to lower case and delete myltiply spaces
std::string GetRightLine(std::string& patternS) {
    std::string res = "";

    int patternSLen = patternS.length();

    bool isSpaceFound = false, firstSymbolFound = false;
    for (int i = 0; i < patternSLen; i++)
    {
        char curChar = patternS[i];
        if (curChar != ' ') {
            if (isSpaceFound) res += ' ';
            isSpaceFound = false;

            if (curChar >= 'A' && curChar <= 'Z')
                res += curChar + 32; // 32 is difference between A and a   
            else
                res += curChar;
                       
            firstSymbolFound = true;
        }
        else if (curChar == ' ' && firstSymbolFound) isSpaceFound = true;        
    }

    return res;
}

// Get word's indexes from text
std::vector<int> WordsInd(std::string& text) {
    std::vector<int> result;

    int textLen = text.length();
    for (int i = 0; i < textLen; i++)
        if (text[i] == ' ') result.push_back(i);

    return result;
}

/*
GTAGCGGCG
GTTATAGCTGATCGCGGC GTAGCGGCGAA
*/