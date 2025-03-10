//
// Created by zyc on 25-3-10.
//

#ifndef ZYC_ERRORHANDLE_H
#define ZYC_ERRORHANDLE_H
#include "ZYC_types.h"
#include "log.h"

void OsErrHandle(const char *fileName, U32 lineNo, U32 errorNo, U32 paraLen, void *para);

#endif //ZYC_ERRORHANDLE_H
