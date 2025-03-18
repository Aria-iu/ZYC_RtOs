//
// Created by zyc on 25-3-17.
//
#include "ZYC_task.h"
#include "ZYC_error.h"
#include "list_external.h"
#include "task.h"
#include "task_external.h"
#include "mem.h"

/* Unused TCBs and ECBs that can be allocated. */
struct TagListObject g_tskCbFreeList = LIST_OBJECT_INIT(g_tskCbFreeList);
struct TagListObject g_tskRecyleList = LIST_OBJECT_INIT(g_tskRecyleList);

extern struct TskModInfo g_tskModInfo;
extern U32 g_tskMaxNum;
extern U32 g_timeSliceCycle;
extern TskEntryFunc g_tskIdleEntry;
extern TaskNameAddFunc g_taskNameAdd;
extern void *OsTskContextInit(U32 taskID, U32 stackSize, uintptr_t *topStack, uintptr_t funcTskEntry);

U32 OsTskRegister(struct TskModInfo *modInfo)
{
      return OS_OK;
}

/*
 * 描述：分配任务栈空间
 */
void *OsTskMemAlloc(U32 size)
{
    void *stackAddr = NULL;
    stackAddr = OsMemAllocAlign((U32)OS_MID_TSK, (U8)OS_MEM_DEFAULT_FSC_PT, size,
                                /* 内存已按16字节大小对齐 */
                                MEM_ADDR_ALIGN_016);
    return stackAddr;
}

U32 OsTaskCreateRsrcInit(U32 taskId, struct TskInitParam *initParam, struct TagTskCb *taskCb,
                                                  uintptr_t **topStackOut, uintptr_t *curStackSize)
{
    U32 ret = OS_OK;
    uintptr_t *topStack = NULL;

    /* 创建任务线程 */
    if (g_taskNameAdd != NULL) {
        ret = g_taskNameAdd(taskId, initParam->name);
        if (ret != OS_OK) {
            return ret;
        }
    }

    /* 查看用户是否配置了任务栈，如没有，则进行内存申请，并标记为系统配置，如有，则标记为用户配置。 */
    if (initParam->stackAddr != 0) {
        topStack = (void *)(initParam->stackAddr);
        taskCb->stackCfgFlg = OS_TSK_STACK_CFG_BY_USER;
    } else {
        topStack = OsTskMemAlloc(initParam->stackSize);
        if (topStack == NULL) {
            ret = OS_ERRNO_TSK_NO_MEMORY;
        } else {
            taskCb->stackCfgFlg = OS_TSK_STACK_CFG_BY_SYS;
        }
    }
    *curStackSize = initParam->stackSize;
    if (ret != OS_OK) {
        return ret;
    }

    *topStackOut = topStack;
    return OS_OK;
}

void OsTskStackInit(U32 stackSize, uintptr_t topStack)
{
//    U32 loop;
//    U32 stackMagicWord = OS_TSK_STACK_MAGIC;
//
//    /* 初始化任务栈，并写入栈魔术字 */
//    for (loop = 1; loop < (stackSize / sizeof(U32)); loop++) {
//        *((U32 *)topStack + loop) = stackMagicWord;
//    }
//    *((U32 *)(topStack)) = OS_TSK_STACK_TOP_MAGIC;
}

void OsTskCreateTcbInit(uintptr_t stackPtr, struct TskInitParam *initParam,
    uintptr_t topStackAddr, uintptr_t curStackSize, struct TagTskCb *taskCb)
{
    /* Initialize the task's stack */
    taskCb->stackPointer = (void *)stackPtr;
    taskCb->args[OS_TSK_PARA_0] = (uintptr_t)initParam->args[OS_TSK_PARA_0];
    taskCb->args[OS_TSK_PARA_1] = (uintptr_t)initParam->args[OS_TSK_PARA_1];
    taskCb->args[OS_TSK_PARA_2] = (uintptr_t)initParam->args[OS_TSK_PARA_2];
    taskCb->args[OS_TSK_PARA_3] = (uintptr_t)initParam->args[OS_TSK_PARA_3];
    taskCb->topOfStack = topStackAddr;
    taskCb->stackSize = curStackSize;
    taskCb->priority = initParam->taskPrio;
    taskCb->origPriority = initParam->taskPrio;
    taskCb->taskEntry = initParam->taskEntry;
    taskCb->lastErr = 0;
    memcpy(taskCb->name,initParam->name, OS_TSK_NAME_LEN);
#if defined(OS_OPTION_RR_SCHED)
    if (initParam->policy == OS_TSK_SCHED_RR) {
        taskCb->policy = OS_TSK_SCHED_RR;
    } else {
        taskCb->policy = OS_TSK_SCHED_FIFO;
    }
    taskCb->startTime = 0;
    taskCb->timeSlice = g_timeSliceCycle;
#if defined(OS_OPTION_RR_SCHED_IRQ_TIME_DISCOUNT)
    taskCb->irqUsedTime = 0;
#endif
#endif
    return;
}

/*
 * 描述：所有任务入口
 */
void OsTskEntry(TskHandle taskId)
{
//    struct TagTskCb *taskCb;
//    uintptr_t intSave;
//
//    (void)taskId;
//
//    taskCb = RUNNING_TASK;
//
//    taskCb->taskEntry(taskCb->args[OS_TSK_PARA_0], taskCb->args[OS_TSK_PARA_1], taskCb->args[OS_TSK_PARA_2],
//                      taskCb->args[OS_TSK_PARA_3]);

    // 调度结束后会开中断，所以不需要自己添加开中断
    // intSave = OsIntLock();

    // OS_TASK_LOCK_DATA = 0;

    /* PRT_TaskDelete不能关中断操作，否则可能会导致它核发SGI等待本核响应时死等 */
    // OsIntRestore(intSave);

    // OsTaskExit(taskCb);
}

/*
 * 描述：创建任务参数检查
 */
U32 OsTaskCreateParaCheck(const TskHandle *taskPid, struct TskInitParam *initParam)
{
    if ((taskPid == NULL) || (initParam == NULL)) {
        return OS_ERRNO_TSK_PTR_NULL;
    }

    if (initParam->taskEntry == NULL) {
        return OS_ERRNO_TSK_ENTRY_NULL;
    }

    if (initParam->stackSize == 0) {
        initParam->stackSize = g_tskModInfo.defaultSize;
    }

    if (((OS_TSK_STACK_SIZE_ALIGN - 1) & initParam->stackSize) != 0) {
        return OS_ERRNO_TSK_STKSZ_NOT_ALIGN;
    }

    if (((OS_TSK_STACK_SIZE_ALIGN - 1) & (uintptr_t)initParam->stackAddr) != 0) {
        return OS_ERRNO_TSK_STACKADDR_NOT_ALIGN;
    }

    if (initParam->stackSize < OS_TSK_MIN_STACK_SIZE) {
        return OS_ERRNO_TSK_STKSZ_TOO_SMALL;
    }
    /* 使用用户内存，则需要包含OS使用的资源，size最小值要包含OS的消耗 */
    if (initParam->stackAddr != 0) {
        if (initParam->stackAddr + initParam->stackSize < initParam->stackAddr) {
            return OS_ERRNO_TSK_STACKADDR_TOO_BIG;
        }
    }

    /* 创建任务线程时做校验 */
    if (initParam->name == NULL || initParam->name[0] == '\0') {
        return OS_ERRNO_TSK_NAME_EMPTY;
    }

    return OS_OK;
}

/*
 * 描述：创建一个任务但不进行激活
 */
U32 OsTaskCreateOnly(TskHandle *taskPid, struct TskInitParam *initParam)
{
    U32 ret;
    U32 taskId;
    // uintptr_t intSave;
    uintptr_t *topStack = NULL;
    void *stackPtr = NULL;
    struct TagTskCb *taskCb = NULL;
    uintptr_t curStackSize = 0;

    ret = OsTaskCreateParaCheck(taskPid, initParam);
    if (ret != OS_OK) {
      	LOGI("error check : OsTaskCreateParaCheck");
        return ret;
    }
    // intSave = OsIntLock();
    // 在此处得到一个空闲的TCB，taskCb指向它。
    ret = OsTaskCreateChkAndGetTcb(&taskCb);
    LOGI("Get tcb : %x", *taskCb);
    LOGI("Get tcb's node : %x", *taskCb.node);

    if (ret != OS_OK) {
        // OsIntRestore(intSave);
        LOGI("error check : OsTaskCreateChkAndGetTcb");
        return ret;
    }
    taskId = taskCb->taskPid;
    ret = OsTaskCreateRsrcInit(taskId, initParam, taskCb, &topStack, &curStackSize);
    if (ret != OS_OK) {
        // OsIntRestore(intSave);
        return ret;
    }
    OsTskStackInit(curStackSize, (uintptr_t)topStack);
    stackPtr = OsTskContextInit(taskId, curStackSize, topStack, (uintptr_t)OsTskEntry);
    OsTskCreateTcbInit((uintptr_t)stackPtr, initParam, (uintptr_t)topStack, curStackSize, taskCb);
    taskCb->taskStatus = OS_TSK_SUSPEND | OS_TSK_INUSE;
    // 出参ID传出
    *taskPid = taskId;
    /*
    // OsIntRestore(intSave);
    */
    return OS_OK;
}

/*
 * 描述：创建一个任务但不进行激活
 */
U32 PRT_TaskCreate(TskHandle *taskPid, struct TskInitParam *initParam)
{
      return OsTaskCreateOnly(taskPid, initParam);
}
