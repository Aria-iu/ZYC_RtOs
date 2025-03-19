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

void dump_tskCbArray(void){
	int i;
	LOGI("TCB's address is :\n");
	for(i=0; i<OS_MAX_TCB_NUM; i++)
		LOGI("TCB[%d]: %x\n", i, g_tskCbArray[i].node);
}

void dump_per_tskCbArray(int i){
	// LOGI("g_tskCbArray[%d] 					is %x\n",i,((struct TagTskCb *)&g_tskCbArray[i]));
	LOGI("g_tskCbArray[%d].node 			is %x\n",i,g_tskCbArray[i].node);
	LOGI("g_tskCbArray[%d].stackPointer 	is %x\n",i,g_tskCbArray[i].stackPointer);
	LOGI("g_tskCbArray[%d].stackSize 		is %x\n",i,g_tskCbArray[i].stackSize);
	LOGI("g_tskCbArray[%d].taskPid 			is %d\n",i,g_tskCbArray[i].taskPid);
}
void dump_my_task_status(void){
	int i;
	for(i=1; i<=g_tskMaxNum; i++){
			dump_per_tskCbArray(i);
	}
}

void dump_g_tskCbFreeList(void){
	LOGI("g_tskCbFreeList's next is %x\n",g_tskCbFreeList.next);
	LOGI("g_tskCbFreeList's next next is %x\n",g_tskCbFreeList.next->next);
	LOGI("g_tskCbFreeList's next next next is %x\n",g_tskCbFreeList.next->next->next);
	LOGI("g_tskCbFreeList's prev is %x\n",g_tskCbFreeList.prev);
	LOGI("g_tskCbFreeList's prev prev is %x\n",g_tskCbFreeList.prev->prev);
	LOGI("g_tskCbFreeList's prev prev prev is %x\n",g_tskCbFreeList.prev->prev->prev);
}

extern struct TskContext;
void dump_task(int i){
    LOGI("TCB'node: %x\n",g_tskCbArray[i].node);
    LOGI("TCB'stackPointer: %x\n",g_tskCbArray[i].stackPointer);
    LOGI("TCB'stackSize: %x\n",g_tskCbArray[i].stackSize);
    LOGI("TCB'taskPid: %x\n",g_tskCbArray[i].taskPid);
    LOGI("TCB'priority: %x\n",g_tskCbArray[i].priority);
    LOGI("TCB'stackCfgFlg: %x\n",g_tskCbArray[i].stackCfgFlg);
    LOGI("TCB'topOfStack: %x\n",g_tskCbArray[i].topOfStack);
    LOGI("TCB'taskEntry: %x\n",g_tskCbArray[i].taskEntry);
    LOGI("TCB'name is: %s\n",g_tskCbArray[i].name);
    struct TskContext *TEMP_stack = (struct TskContext *)g_tskCbArray[i].stackPointer;
    LOGI("x01 is %x\n",TEMP_stack->x01);
}

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
	LOGI("OS_MAX_TCB_NUM = %d\n", OS_MAX_TCB_NUM);
    LOGI("sizeof TagTskCb is %x\n", size/OS_MAX_TCB_NUM);
    g_tskCbArray = (struct TagTskCb *)OsMemAllocAlign((U32)OS_MID_TSK, OS_MEM_DEFAULT_FSC_PT,
                                                      size, MEM_ADDR_ALIGN_016);
	if (g_tskCbArray == NULL) {
        return OS_ERRNO_TSK_NO_MEMORY;
    }
	LOGI("g_tskCbArray 's address is %x\n", g_tskCbArray);
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

