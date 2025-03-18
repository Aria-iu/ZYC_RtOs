//
// Created by zyc on 25-3-17.
//
#include "ZYC_task.h"
#include "ZYC_mem.h"
#include "task.h"
#include "task_external.h"
#include "mem.h"
#include "fsc_mem.h"

struct TskModInfo g_tskModInfo;

U32 g_tskMaxNum;
U32 g_tskBaseId;
U32 g_timeSliceCycle = (U32_MAX - 1);

TskEntryFunc g_tskIdleEntry;

TaskNameAddFunc g_taskNameAdd;

#define g_maxNumOfCores 1
#define OS_MAX_TCB_NUM                  (g_tskMaxNum + 1 + g_maxNumOfCores)
U32 g_tskMaxNum;
struct TagTskCb *g_tskCbArray;

/*
 * 描述：任务初始化
 */
U32 OsTskInit(void)
{
	uintptr_t size;
    U32 idx;
	g_tskMaxNum = 3;
   	g_tskBaseId = 1;
    size = (OS_MAX_TCB_NUM) * sizeof(struct TagTskCb);

    g_tskCbArray = (struct TagTskCb *)OsMemAllocAlign((U32)OS_MID_TSK, OS_MEM_DEFAULT_FSC_PT,
                                                      size, MEM_ADDR_ALIGN_016);

	if (g_tskCbArray == NULL) {
        return OS_ERRNO_TSK_NO_MEMORY;
    }

	/* Connect all the TCBs in a doubly linked list. */
	OS_LIST_INIT(&g_tskCbFreeList);
    for (idx = 0; idx < OS_MAX_TCB_NUM - 1; idx++) {
        g_tskCbArray[idx].taskStatus = OS_TSK_UNUSED;
        g_tskCbArray[idx].taskPid = (idx + g_tskBaseId);
        ListTailAdd(&g_tskCbArray[idx].node, &g_tskCbFreeList);
    }
	return OS_OK;
}

