#include "ControlFlow/IdGetter.h"

#include <fstream>
#include <iostream>

using namespace std;

void registerResourceId(const string& resourseFilePath, int& resourceIdNum, BlockIdObj resourceIdList[maxBlockId]) {
    ifstream resourceFile{resourseFilePath};  // One resource file is opened.

    int blockId = 0;
    string line;
    while (getline(resourceFile, line)) {  // Read all the lines in resourceFile, line is read.

        // If the start of the line is "block.", and no duplicate confirmed, register block ID.
        if ((line.substr(0, 6) == "block.") && (blockId < stoi(line.substr(6, 5)))) {
            if (!(isdigit(line[6])) || !(isdigit(line[7])) || !(isdigit(line[8])) || !(isdigit(line[9])) ||
                !(isdigit(line[10])) || (line[11] != '=') || (line[12] == ' ')) {  // Syntax error catcher
                cerr << "ERROR: Some content(s) in resource file have invalid format!" << endl;
                system("pause");
                exit(1);
            }

            blockId = stoi(line.substr(6, 5));
            resourceIdList[resourceIdNum].setId(blockId);
            resourceIdNum++;

            if (resourceIdNum > maxBlockId - 1) {  // Error catcher.
                cerr << "ERROR: Too many block IDs in resource file! (max: " << maxBlockId << ")" << endl;
                system("pause");
                exit(1);
            }
        }
    }

    // Print number of block IDs in resource file.
    clog << "There are " << resourceIdNum << " block IDs in resource file." << endl;

    resourceFile.close();
}

void registerSearchId(const string& resourceFilePath, BlockIdObj resourceIdList[maxBlockId], const int resourceIdNum,
                      BlockIdObj searchIdList[maxBlockId], int& searchIdNum, const string& searchTarget) {
    ifstream resourceFile{resourceFilePath};  // One resource file is opened.

    bool isIdFound;
    string line;
    int blockId;
    for (int idCnt = 0; idCnt < resourceIdNum; idCnt++) {
        isIdFound = false;
        while (!isIdFound) {
            getline(resourceFile, line);
            if ((line.substr(0, 6) == "block.") && (resourceIdList[idCnt].getBlockId() == stoi(line.substr(6, 5)))) {
                isIdFound = true;
                if (line.find(searchTarget, 0) != string::npos) {
                    blockId = resourceIdList[idCnt].getBlockId();
                    searchIdList[searchIdNum].setId(blockId);
                    searchIdNum++;
                }
            }
        }
    }

    // Print number of block IDs in resource file. If there is no block ID, terminate.
    if (searchIdNum == 0) {
        clog << "There is no block ID in resource file that contain the word you are searching for. There is "
                "noting to do. Terminating."
             << endl;
        system("pause");
        exit(0);
    } else if (searchIdNum == 1) {
        clog << "There is " << searchIdNum << " block ID in resource file that contain the word you are searching for."
             << endl;
    } else {
        clog << "There are " << searchIdNum
             << " block IDs in resource file that contain the word you are searching for." << endl;
    }

    resourceFile.close();
}