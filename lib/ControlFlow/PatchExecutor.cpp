#include "ControlFlow/PatchExecutor.h"

#include <fstream>
#include <iostream>

using namespace std;

void doExtract(const OneBlockId* const searchOneBlockIdList, const int searchOneBlockIdNum, const string& pathOfResult,
               const string& searchTarget) {
    int extractedWordNum = 0;
    string res = "";

    for (int idCnt = 0; idCnt < searchOneBlockIdNum; idCnt++) {
        if (idCnt != 0) {
            res += '\n';
        }
        res += "block.";
        res += to_string(searchOneBlockIdList[idCnt].getBlockId());
        res += "=";

        res += searchOneBlockIdList[idCnt].getWord(0);
        extractedWordNum++;
        for (int wordCnt = 1; wordCnt < searchOneBlockIdList[idCnt].getWordNum(); wordCnt++) {
            res += " ";
            res += searchOneBlockIdList[idCnt].getWord(wordCnt);
            extractedWordNum++;
        }

        res += "\n";
    }

    ofstream resultFile{pathOfResult};
    resultFile.write(res.c_str(), res.size());

    resultFile.close();
    // Patch completed.

    // Print patch result.
    clog << "Extract process completed successfully!" << endl;

    if (extractedWordNum == 1) {
        clog << "Word Extracted: " << extractedWordNum << endl;
    } else {
        clog << "Words Extracted: " << extractedWordNum << endl;
    }
}