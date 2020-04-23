#pragma once

#include <map>
#include <string>
#include "CMDMapping.h"
#include <memory>

void GetHelp();
void ReadParam(const CMDMapping &inpMap);
void WriteParam(const CMDMapping& inpMap);