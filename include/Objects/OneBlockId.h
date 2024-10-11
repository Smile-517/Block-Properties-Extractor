#pragma once

#include <string>

#include "Config.h"
#include "Objects/BlockIdObj.h"

using namespace std;

class OneBlockId : public BlockIdObj {
   public:
    // Constructor
    OneBlockId();

    // Getters
    const string& getWord(const int index) const;
    int getWordNum() const;
    static int getAllWordNum(const OneBlockId* const oneBlockIdList, const int oneBlockIdNum);

    // Methods
    void registerLine(string& line, const string& searchTarget, OneBlockId* const searchOneBlockIdList,
                      const int searchOneBlockIdNum);

   protected:
    // Member variables
    string wordList[maxWord];  // List that will store all the words for 1 block ID.
    int wordNum;               // Number of words in 1 block ID.

    // Protected methods
    void searchInsertWord(const string& word, const string& searchTarget, const int targetBlockId,
                          OneBlockId* const searchOneBlockIdList, const int searchOneBlockIdNum);
};