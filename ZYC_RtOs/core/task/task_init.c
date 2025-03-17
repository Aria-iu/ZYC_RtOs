//
// Created by zyc on 25-3-17.
//
#include "ZYC_task.h"
#include "ZYC_error.h"


extern struct TskModInfo g_tskModInfo;
extern U32 g_tskMaxNum;
extern U32 g_timeSliceCycle;
extern TskEntryFunc g_tskIdleEntry;

U32 OsTskRegister(struct TskModInfo *modInfo)
{

//    if (((modInfo->maxNum) > (MAX_TASK_NUM)) || (modInfo->maxNum == 0)) {
//        return OS_ERRNO_TSK_MAX_NUM_NOT_SUITED;
//    }
//
//    g_tskModInfo.maxNum = modInfo->maxNum;
//    g_tskModInfo.defaultSize = modInfo->defaultSize;
//    g_tskModInfo.idleStackSize = modInfo->idleStackSize;
//    g_tskModInfo.magicWord = modInfo->magicWord;
//    if (modInfo->timeSliceMs == 0) {
//        g_tskModInfo.timeSliceMs = OS_TSK_DEFAULT_TIME_SLICE_MS;
//    } else {
//        g_tskModInfo.timeSliceMs = modInfo->timeSliceMs;
//    }
//
//    /* system clock 正常远大于1000 */
//    g_timeSliceCycle = (g_systemClock / OS_SYS_MS_PER_SECOND) * g_tskModInfo.timeSliceMs;
//
//    /* task模块有动态加载的场景 */
//    if (g_tskIdleEntry == NULL) {
//        g_tskIdleEntry = (TskEntryFunc)OsTskIdleBgd;
//    }
//
//    g_tskMaxNum = g_tskModInfo.maxNum;
//
      return OS_OK;

}


/*
 * 描述：创建一个任务但不进行激活
 */
U32 OsTaskCreateOnly(TskHandle *taskPid, struct TskInitParam *initParam)
{
    U32 ret;
    U32 taskId;
    uintptr_t intSave;
    uintptr_t *topStack = NULL;
    void *stackPtr = NULL;
    struct TagTskCb *taskCb = NULL;
    uintptr_t curStackSize = 0;

    ret = OsTaskCreateParaCheck(taskPid, initParam);
    if (ret != OS_OK) {
        return ret;
    }
    intSave = OsIntLock();
    ret = OsTaskCreateChkAndGetTcb(&taskCb);
    if (ret != OS_OK) {
        OsIntRestore(intSave);
        return ret;
    }

    taskId = taskCb->taskPid;

    ret = OsTaskCreateRsrcInit(taskId, initParam, taskCb, &topStack, &curStackSize);
    if (ret != OS_OK) {
        ListAdd(&taskCb->pendList, &g_tskCbFreeList);
        OsIntRestore(intSave);
        return ret;
    }
    OsTskStackInit(curStackSize, (uintptr_t)topStack);

    stackPtr = OsTskContextInit(taskId, curStackSize, topStack, (uintptr_t)OsTskEntry);

    OsTskCreateTcbInit((uintptr_t)stackPtr, initParam, (uintptr_t)topStack, curStackSize, taskCb);

    taskCb->taskStatus = OS_TSK_SUSPEND | OS_TSK_INUSE;
    // 出参ID传出
    *taskPid = taskId;
    OsIntRestore(intSave);
    return OS_OK;
}

/*
 * 描述：创建一个任务但不进行激活
 */
U32 PRT_TaskCreate(TskHandle *taskPid, struct TskInitParam *initParam)
{
      return OsTaskCreateOnly(taskPid, initParam);
}
