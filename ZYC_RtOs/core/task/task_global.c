//
// Created by zyc on 25-3-17.
//
#include "ZYC_task.h"

struct TskModInfo g_tskModInfo;

U32 g_tskMaxNum;

U32 g_timeSliceCycle = (U32_MAX - 1);

TskEntryFunc g_tskIdleEntry;

