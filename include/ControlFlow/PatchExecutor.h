#pragma once

#include "Objects/OneBlockId.h"

using namespace std;

// Search for the words user wants and write it in result folder.
void doExtract(const OneBlockId* const searchOneBlockIdList, const int searchOneBlockIdNum, const string& pathOfResult,
               const string& searchTarget);