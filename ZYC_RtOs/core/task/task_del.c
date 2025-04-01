//
//// Created by zyc on 25-3-17.
////
#include "ZYC_task.h"
#include "ZYC_error.h"
#include "list_external.h"
#include "task.h"
#include "task_external.h"
#include "mem.h"

extern struct TagTskCb *g_tskCbArray;


void TskExit(int Tskid){
	PRT_MemFree(0,g_tskCbArray[Tskid].saveAllocStack);
	g_tskCbArray[Tskid].stackSize=0;
}
