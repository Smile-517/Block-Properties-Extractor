#pragma once

#include <string>

#include "Config.h"
#include "Objects/BlockIdObj.h"

using namespace std;

// Read resource file and make block ID list.
void registerResourceId(const string& resourseFilePath, int& resourceIdNum, BlockIdObj resourceIdList[maxBlockId]);

// Read resource file and make block ID list.
void registerSearchId(const string& resourceFilePath, BlockIdObj resourceIdList[maxBlockId], const int resourceIdNum,
                      BlockIdObj searchIdList[maxBlockId], int& searchIdNum, const string& searchTarget);