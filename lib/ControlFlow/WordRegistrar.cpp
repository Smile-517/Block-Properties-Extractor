#include "ControlFlow/WordRegistrar.h"

#include <fstream>
#include <iostream>

using namespace std;

OneBlockId* makeOneBlockIdList(const BlockIdObj idListIn[maxBlockId], const int idNumIn) {
    OneBlockId* const oneBlockIdList = new OneBlockId[idNumIn];
    for (int i = 0; i < idNumIn; i++) {
        oneBlockIdList[i].setId(idListIn[i].getBlockId());
    }

    return oneBlockIdList;
}

void registerResourceWord(const string& resourceFilePath, OneBlockId* const searchOneBlockIdList,
                          const int searchOneBlockIdNum, const string& searchTarget) {
    // Open resourceFile
    ifstream resourceFile{resourceFilePath};

    // Read all the lines in resource file and register words to searchOneBlockIdList.
    string line;
    string targetBlockId;
    bool isRegistered;
    for (int idCnt = 0; idCnt < searchOneBlockIdNum; idCnt++) {
        isRegistered = false;
        while (!isRegistered) {
            getline(resourceFile, line);
            if ((line.substr(0, 6) == "block.") &&
                (stoi(line.substr(6, 5)) == searchOneBlockIdList[idCnt].getBlockId())) {
                // Remove all the useless whitespaces.
                while (line[line.length() - 1] == ' ') {
                    line.erase(line.length() - 1);
                }

                searchOneBlockIdList[idCnt].registerLine(line, searchTarget, searchOneBlockIdList, searchOneBlockIdNum);
                isRegistered = true;
            }
        }
    }  // Register progress completed.

    resourceFile.close();

    clog << OneBlockId::getAllWordNum(searchOneBlockIdList, searchOneBlockIdNum) << " words found in resource file."
         << endl;
}