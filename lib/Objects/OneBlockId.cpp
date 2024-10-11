#include "Objects/OneBlockId.h"

#include <iostream>

using namespace std;

// Constructor
OneBlockId::OneBlockId() : BlockIdObj(), wordNum(0) {}

// Getters
const string& OneBlockId::getWord(const int index) const { return wordList[index]; }
int OneBlockId::getWordNum() const { return wordNum; }
int OneBlockId::getAllWordNum(const OneBlockId* const oneBlockIdList, const int oneBlockIdNum) {
    int allWordNum = 0;
    for (int i = 0; i < oneBlockIdNum; i++) {
        allWordNum += oneBlockIdList[i].getWordNum();
    }
    return allWordNum;
}

// Methods
void OneBlockId::registerLine(string& line, const string& searchTarget, OneBlockId* const searchOneBlockIdList,
                              const int searchOneBlockIdNum) {  // line looks like "block.10012=vine dirt stone"
    int targetBlockId = stoi(line.substr(6, 5));
    line.erase(0, 12);  // And now, line looks like "vine dirt stone"

    int spacePos = line.find(" ");
    int cutLineLength = line.length();
    if (spacePos != string::npos) {  // There are some words (2 or more).
        int cursorPos = 0;
        int wordLength;
        string word;
        while (spacePos != string::npos) {  // Search for all whitespaces.
            wordLength = spacePos - cursorPos;

            word = line.substr(cursorPos, wordLength);
            searchInsertWord(word, searchTarget, targetBlockId, searchOneBlockIdList, searchOneBlockIdNum);

            cursorPos = spacePos + 1;
            spacePos = line.find(" ", cursorPos);
        }

        // Register last word.
        if (cursorPos < cutLineLength) {  // So, "vine dirt stone " is not the case.
            word = line.substr(cursorPos);
            searchInsertWord(word, searchTarget, targetBlockId, searchOneBlockIdList, searchOneBlockIdNum);
        }
    } else if ((spacePos == string::npos) && (cutLineLength != 0)) {  // There is 1 word.
        searchInsertWord(line, searchTarget, targetBlockId, searchOneBlockIdList, searchOneBlockIdNum);
    }  // If there is nothing, nothing happens.
}

// Protected methods
void OneBlockId::searchInsertWord(const string& wordIn, const string& searchTarget, const int targetBlockId,
                                  OneBlockId* const searchOneBlockIdList, const int searchOneBlockIdNum) {
    if (wordIn.find(searchTarget, 0) != string::npos) {
        // Check for duplicated words in resource file.
        for (int idCnt = 0; idCnt < searchOneBlockIdNum; idCnt++) {
            for (int wordCnt = 0; wordCnt < searchOneBlockIdList[idCnt].getWordNum(); wordCnt++) {
                if (wordIn == searchOneBlockIdList[idCnt].getWord(wordCnt)) {
                    if (searchOneBlockIdList[idCnt].getBlockId() != targetBlockId) {
                        cerr << "ERROR: A word \'" << wordIn << "\' is in both block."
                             << searchOneBlockIdList[idCnt].getBlockId() << " and block." << targetBlockId
                             << " in resource file. Please resolve the duplication in the resource file!" << endl;
                        system("pause");
                        exit(1);
                    } else {  // searchOneBlockIdList[idCnt].getBlockId() == targetBlockId
                        cerr << "ERROR: A word \'" << wordIn << "\' in block." << targetBlockId
                             << " in resource file is duplicated. Please resolve the duplication in the resource file!"
                             << endl;
                        system("pause");
                        exit(1);
                    }
                }
            }
        }

        wordList[wordNum] = wordIn;
        wordNum++;

        if (wordNum > maxWord - 1) {
            cerr << "ERROR: Too many words at block." << blockId << " in resource file! (max: " << maxWord << ")"
                 << endl;
            system("pause");
            exit(1);
        }
    }
}