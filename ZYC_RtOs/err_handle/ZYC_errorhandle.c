//
// Created by zyc on 25-3-10.
//

#include "ZYC_errorhandle.h"
#include "ZYC_error.h"

void OsErrHandle(const char *fileName, U32 lineNo, U32 errorNo, U32 paraLen, void *para)
{
    LOGE("%s:%ld\n", fileName, lineNo);
}

void OsAsmIll(void)
{
    LOGE("kernel wrong!!!");
    OS_EMBED_ASM("svc  0");
}
