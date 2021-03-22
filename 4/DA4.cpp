#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <stdio.h>
#include "BM.hpp"

#include <time.h>

// Get line of text from input and convert upper case chars to lower
bool GetLine(std::vector<std::string>& vct);
// Get text but with C-style input
void ReadText(std::vector<std::pair<std::string, std::pair<int, int> > >& vct);

int main()
{
    std::vector<std::string> pattern;
    if (!GetLine(pattern)) // If pattern is empty
        return 0;

    std::unordered_map<std::string, std::vector<int> > patternBadSymbol = BM::RulerBadSymbol(pattern);
    std::pair<std::vector<int>, std::vector<int> > patternGoodSuffix = BM::RulerGoodSuffix(pattern);    

    // std::string is word
    // std::pair first is line's index in text
    // std::pair second is word's index in line
    std::vector<std::pair<std::string, std::pair<int, int> > > text;

    // // Text reading
    ReadText(text);

    std::vector<std::pair<int, int> > result;
    int leftPatternPosition = 0;
    while (leftPatternPosition + pattern.size() <= text.size()) {
        for (int i = pattern.size() - 1; i >= 0; --i) {
            std::string& currentWord = text[leftPatternPosition + i].first;
            if (currentWord != pattern[i]) {
                int badRuler = BM::FindBadSymbol(patternBadSymbol, currentWord, i + 1);
                int goodRuler = BM::FindGoodSuffix(patternGoodSuffix, i + 1);
                if (badRuler == 0 && goodRuler == 0) {
                    ++leftPatternPosition;
                }
                else if (badRuler > goodRuler) {
                    leftPatternPosition += badRuler;
                }
                else {
                    leftPatternPosition += goodRuler;
                }
                break;
            }
            else if (i == 0) {
                result.push_back(text[leftPatternPosition + i].second);
                int goodRuler = BM::FindGoodSuffix(patternGoodSuffix, 0);
                if (goodRuler == 0) {
                    ++leftPatternPosition;
                }
                else {
                    leftPatternPosition += goodRuler;
                }
            }
        }
    }
    
    for (const auto& item : result)
        printf("%d, %d\n", item.first, item.second);
    return 0;
}

bool GetLine(std::vector<std::string>& vct) {
    std::string currentString;
    if (!std::getline(std::cin, currentString) || currentString == "\x4")
        return false;
    std::stringstream ss(currentString);
    std::string wordFromLine;
    while (ss >> wordFromLine) {
        // Converts letters to lowercase
        for (char& ch : wordFromLine)
            ch = tolower(ch);

        vct.push_back(wordFromLine);
    }

    return true;
}

void ReadText(std::vector<std::pair<std::string, std::pair<int, int> > >& vct){
    std::string buffer = "";
    char currentChar;
    int wordCount = 1, lineCount = 1;
    while((currentChar = std::getchar()) && (currentChar != EOF)){
        currentChar = tolower(currentChar);
        if(currentChar == ' ' || currentChar == '\n'){
            if(buffer != "")
                vct.push_back({buffer, {lineCount, wordCount++}});
            if(currentChar == '\n'){
                ++lineCount;
                wordCount = 1;
            }
            buffer = "";
            continue;
        }
        buffer += currentChar;
    }
}
