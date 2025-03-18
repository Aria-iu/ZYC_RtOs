## 任务管理初始化

为需要创建的任务分配TCB控制块：将创建的空闲TCB链接到链表g_tskCbFreeList中，创建任务时可以从中分配空闲TCB。
```c
U32 OsTskInit(void)
{
	uintptr_t size;
    U32 idx;
    // 要使用的任务数量，暂时设置为 3
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
    // 这里我们略过 第一个分配的 g_tskCbArray[0]
    for (idx = 1; idx < OS_MAX_TCB_NUM - 1; idx++) {
        g_tskCbArray[idx].taskStatus = OS_TSK_UNUSED;
        g_tskCbArray[idx].taskPid = (idx + g_tskBaseId);
        ListTailAdd(&g_tskCbArray[idx].node, &g_tskCbFreeList);
    }
	return OS_OK;
}
```

```
Started cell "inmate-demo-1"
[ZYC_RtOs : INFO] : System alloc mem : begin 2458 , end 12458
[ZYC_RtOs : INFO] : task init begin
[ZYC_RtOs : INFO] : fsc : g_fscMemBitMap is 0x10001
[ZYC_RtOs : INFO] : fsc : g_memTotalSize is 0xffe0
[ZYC_RtOs : INFO] : fsc : g_memUsage is 0x0
[ZYC_RtOs : INFO] : fsc : g_memPeakUsage is 0x0
[ZYC_RtOs : INFO] : fsc : g_memStartAddr is 0x2458
[ZYC_RtOs : INFO] : OS_MAX_TCB_NUM = 5
[ZYC_RtOs : INFO] : sizeof TagTskCb is 80
[ZYC_RtOs : INFO] : g_tskCbArray 's address is 121b0
[ZYC_RtOs : INFO] : task init end
[ZYC_RtOs : INFO] : fsc : g_fscMemBitMap is 0x10001
[ZYC_RtOs : INFO] : fsc : g_memTotalSize is 0xffe0
[ZYC_RtOs : INFO] : fsc : g_memUsage is 0x2b0
[ZYC_RtOs : INFO] : fsc : g_memPeakUsage is 0x2b0
[ZYC_RtOs : INFO] : fsc : g_memStartAddr is 0x2458
[ZYC_RtOs : INFO] : g_tskCbArray[1] 					is 17ef0
[ZYC_RtOs : INFO] : g_tskCbArray[1].node 			is 160a8
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].taskPid 			is 2
[ZYC_RtOs : INFO] : g_tskCbArray[2] 					is 17ef0
[ZYC_RtOs : INFO] : g_tskCbArray[2].node 			is 12230
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].taskPid 			is 3
[ZYC_RtOs : INFO] : g_tskCbArray[3] 					is 17ef0
[ZYC_RtOs : INFO] : g_tskCbArray[3].node 			is 122b0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].taskPid 			is 4
[ZYC_RtOs : INFO] : g_tskCbFreeList's next is 12230
[ZYC_RtOs : INFO] : g_tskCbFreeList's next next is 122b0
[ZYC_RtOs : INFO] : g_tskCbFreeList's next next next is 12330
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev is 12330
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev prev is 122b0
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev prev prev is 12230
```
## 创建任务

```c
#include <inmate.h>
#include "log.h"
#include "mem.h"
#include "task.h"
#include "ZYC_task.h"
#include "ZYC_mem.h"
#include "fsc_mem.h"

TskHandle g_testTskHandle;
void TestTaskEntry()
{
    LOGI("This is task test's entry!!!\n");
}

U32 OsTestInit(void)
{
    U32 ret;
    U8 ptNo = OS_MEM_DEFAULT_FSC_PT;
    struct TskInitParam param = {0};

    param.stackAddr = PRT_MemAllocAlign(0, ptNo, 0x2000, MEM_ADDR_ALIGN_016);
    param.taskEntry = (TskEntryFunc)TestTaskEntry;
    param.taskPrio = 25;
    param.name = "TestTask";
    param.stackSize = 0x2000;

    ret = PRT_TaskCreate(&g_testTskHandle, &param);
    if (ret) {
        return ret;
    }
    return OS_OK;
}

void inmate_main(void)
{
    log_init(LOG_INFO);
    mem_detect();
    mem_init();
    LOGI("task init begin\n");

    LOGI("fsc : g_fscMemBitMap is 0x%x\n",g_fscMemBitMap);
    LOGI("fsc : g_memTotalSize is 0x%x\n",g_memTotalSize);
    LOGI("fsc : g_memUsage is 0x%x\n",g_memUsage);
    LOGI("fsc : g_memPeakUsage is 0x%x\n",g_memPeakUsage);
    LOGI("fsc : g_memStartAddr is 0x%x\n",g_memStartAddr);

    OsTskInit();

    LOGI("task init end\n");

    LOGI("fsc : g_fscMemBitMap is 0x%x\n",g_fscMemBitMap);
    LOGI("fsc : g_memTotalSize is 0x%x\n",g_memTotalSize);
    LOGI("fsc : g_memUsage is 0x%x\n",g_memUsage);
    LOGI("fsc : g_memPeakUsage is 0x%x\n",g_memPeakUsage);
    LOGI("fsc : g_memStartAddr is 0x%x\n",g_memStartAddr);

    dump_my_task_status();
    
    dump_g_tskCbFreeList();

    OsTestInit(); 

    LOGI("g_testTskHandle is %d\n",g_testTskHandle);
    dump_my_task_status();

}


```

```
Started cell "inmate-demo-1"
[ZYC_RtOs : INFO] : System alloc mem : begin 2460 , end 12460
[ZYC_RtOs : INFO] : task init begin
[ZYC_RtOs : INFO] : fsc : g_fscMemBitMap is 0x10001
[ZYC_RtOs : INFO] : fsc : g_memTotalSize is 0xffe0
[ZYC_RtOs : INFO] : fsc : g_memUsage is 0x0
[ZYC_RtOs : INFO] : fsc : g_memPeakUsage is 0x0
[ZYC_RtOs : INFO] : fsc : g_memStartAddr is 0x2460
[ZYC_RtOs : INFO] : OS_MAX_TCB_NUM = 5
[ZYC_RtOs : INFO] : sizeof TagTskCb is 80
[ZYC_RtOs : INFO] : g_tskCbArray 's address is 121b0
[ZYC_RtOs : INFO] : task init end
[ZYC_RtOs : INFO] : fsc : g_fscMemBitMap is 0x10001
[ZYC_RtOs : INFO] : fsc : g_memTotalSize is 0xffe0
[ZYC_RtOs : INFO] : fsc : g_memUsage is 0x2b0
[ZYC_RtOs : INFO] : fsc : g_memPeakUsage is 0x2b0
[ZYC_RtOs : INFO] : fsc : g_memStartAddr is 0x2460
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[1]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[1].node 			is 166f8
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].taskPid 			is 2
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[1].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[2]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[2].node 			is 12230
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].taskPid 			is 3
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[2].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[3]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[3].node 			is 122b0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].taskPid 			is 4
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[3].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbFreeList's next is 12230
[ZYC_RtOs : INFO] : g_tskCbFreeList's next next is 122b0
[ZYC_RtOs : INFO] : g_tskCbFreeList's next next next is 12330
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev is 12330
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev prev is 122b0
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev prev prev is 12230
[ZYC_RtOs : INFO] : g_testTskHandle is 2
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[1]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[1].node 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackPointer 	is 12060
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackSize 		is 2000
[ZYC_RtOs : INFO] : g_tskCbArray[1].taskPid 			is 2
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackCfgFlg 			is 1
[ZYC_RtOs : INFO] : g_tskCbArray[1].priority 			is 25
[ZYC_RtOs : INFO] : g_tskCbArray[1].topOfStack 			is 0x10180
[ZYC_RtOs : INFO] : g_tskCbArray[1].name 			is TestTask
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[2]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[2].node 			is 166f8
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].taskPid 			is 3
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[2].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[3]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[3].node 			is 122b0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].taskPid 			is 4
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[3].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------

```

可以看到，已经为系统初始化了三个空闲TCB，每创建一个任务，需要一个空闲TCB，当空闲TCB用完时，不能继续创建任务，用户可以自己定义需要多少任务。

下一步是运行所创建的任务。

在任务调度管理时，计划有两种方式，一种是FIFO，一个个执行任务，直到没有任务为止。另一种是优先级调度，持续执行优先级最高的任务，直到没有任务为止。