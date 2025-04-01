//
// Created by zyc on 25-3-17.
//

#ifndef TASK_EXTERNAL_H
#define TASK_EXTERNAL_H

#include "ZYC_types.h"
#include "ZYC_task.h"
#include "list_external.h"

extern struct TagListObject g_tskCbFreeList;

#define OS_TSK_STACK_CFG_BY_USER 1
#define OS_TSK_STACK_CFG_BY_SYS  0

#define OS_TSK_PARA_0   0
#define OS_TSK_PARA_1   1
#define OS_TSK_PARA_2   2
#define OS_TSK_PARA_3   3

#define OsIntUnLock() PRT_HwiUnLock()
#define OsIntLock()   PRT_HwiLock()
#define OsIntRestore(intSave) PRT_IntRestore(intSave)

/*
 * 任务线程及进程控制块的结构体统一定义。
 */
struct TagTskCb {
  	struct TagListObject node;
    /* 当前任务的SP */
    void *stackPointer;
    /* 任务状态,后续内部全改成U32 */
    U32 taskStatus;
    /* 任务的运行优先级，数字越小优先级越高 */
    TskPrior priority;
    /* 任务栈配置标记 */
    U16 stackCfgFlg;
    /* 任务栈大小 */
    U32 stackSize;
    TskHandle taskPid;
    /* 任务栈顶 */
    uintptr_t topOfStack;
    /* 任务入口函数 */
    TskEntryFunc taskEntry;
    /* 任务的参数 */
    uintptr_t args[4];
    /* 存放任务名 */
    char name[OS_TSK_NAME_LEN];
    /* 任务原始优先级 */
    TskPrior origPriority;
    /* 调度策略 */
    U16 policy;
    /* 剩余时间片 */
    U32 timeSlice;
    /* 任务记录的最后一个错误码 */
    U32 lastErr;
    /* 任务恢复的时间点(单位Tick) */
    U64 expirationTick;
    uintptr_t saveAllocStack;
};

OS_SEC_ALW_INLINE INLINE U32 OsTaskCreateChkAndGetTcb(struct TagTskCb **taskCb)
{
    *taskCb = ((struct TagTskCb *)((uintptr_t)((&g_tskCbFreeList)->next)));
    // 成功，从空闲列表中移除
    ListDelete((struct TagTskCb *)((uintptr_t)((&g_tskCbFreeList)->next)));
    return OS_OK;
}

#endif //TASK_EXTERNAL_H
