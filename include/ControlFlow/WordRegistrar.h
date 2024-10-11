#pragma once

#include "Config.h"
#include "Objects/BlockIdObj.h"
#include "Objects/OneBlockId.h"

// Make OneBlockId list based on input block ID list.
OneBlockId* makeOneBlockIdList(const BlockIdObj idListIn[maxBlockId], const int idNumIn);

// Read resource file and register words to block IDs.
void registerResourceWord(const string& resourceFilePath, OneBlockId* const searchOneBlockIdList,
                          const int searchOneBlockIdNum, const string& searchTarget);