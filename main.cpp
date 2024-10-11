#include <ctime>
#include <filesystem>
#include <iostream>
#include <string>

#include "Config.h"
#include "ControlFlow/IdGetter.h"
#include "ControlFlow/PatchExecutor.h"
#include "ControlFlow/PathGetter.h"
#include "ControlFlow/WordRegistrar.h"
#include "Objects/BlockIdObj.h"
#include "Objects/OneBlockId.h"
#include "Tester.h"

using namespace std;

int main() {
    clock_t startTime = clock();
    clock_t endTime;
    double duration;
    double timeConsumed = 0;

    // ================================ Start of PathGetter ================================
    // Open resource folder.
    string searchTargetTemp;
    const string resourceFilePath = getResourceFilePath(dirResource, searchTargetTemp, timeConsumed);
    const string searchTarget = searchTargetTemp;

    // Check if the searchTarget.properties file exists in result folder.
    const string pathOfResult = checkResultFile(dirResult, searchTarget, timeConsumed);
    // ================================= End of PathGetter =================================

    // ================================ Start of IdGetter ================================
    clog << '\n';

    // Read resource file and make resource block ID list.
    int resourceIdNum = 0;
    BlockIdObj resourceIdList[maxBlockId];  // So, this program supports up to (maxBlockId) block IDs.
    registerResourceId(resourceFilePath, resourceIdNum, resourceIdList);

    int searchIdNum = 0;
    BlockIdObj searchIdList[maxBlockId];
    registerSearchId(resourceFilePath, resourceIdList, resourceIdNum, searchIdList, searchIdNum, searchTarget);

    // TEST: Print all the block IDs in resource file.
    // printAllResourceIds(resourceIdList, resourceIdNum);
    // ================================= End of IdGetter =================================

    // ================================ Start of WordRegistrar ================================
    clog << '\n';

    // Make search block ID list based on search BlockIdObj list.
    int searchOneBlockIdNum = searchIdNum;
    OneBlockId* searchOneBlockIdList = makeOneBlockIdList(searchIdList, searchIdNum);

    // Read resource file and register words to block IDs.
    registerResourceWord(resourceFilePath, searchOneBlockIdList, searchOneBlockIdNum, searchTarget);
    // ================================= End of WordRegistrar =================================

    // ================================ Start of PatchExecutor ================================
    clog << '\n';

    // Search for the words user wants and write it in result folder.
    doExtract(searchOneBlockIdList, searchOneBlockIdNum, pathOfResult, searchTarget);
    // ================================= End of PatchExecutor =================================

    delete[] searchOneBlockIdList;

    endTime = clock();
    duration = endTime - startTime - timeConsumed;
    clog << "Time elapsed: " << duration << "ms" << endl;

    system("pause");
    return 0;
}