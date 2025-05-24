## 任务调度
创建任务之后，TCB 存储在 g_tskCbArray 数组中，用户可以自行定义任务的调度，这里实现了 FIFO 的调度，根据任务创建的先后顺序依次执行。

FIFO 的调度方法最为简单，也是单核嵌入式系统的常见选择，但是有很多缺陷，例如，某个任务中若有等待或其他耗时操作，其他任务无法执行。

### 调度函数
调用 OsMainSchedule ，开启系统调度。
```c
void OsMainSchedule(void)
{
    save_current_context(&g_current_context);
    // we can run this sche once and again and again ...
    int idx = find_tcb_aviliable();
    if (idx == 0||idx>3){
    	LOGI("no more tasks in system , halt");
	while(1){
		// TODO: just sleep cpu here
	    }
    }
    g_running_task_idx = idx;

    LOGI("find index is %d\n",idx);
    LOGI("g_running_task_idx is %d\n",g_running_task_idx);
    LOGI("let's go to task\n");
    LOGI("g_tskCbArray[g_running_task_idx].stackPointer is 0x%x\n",g_tskCbArray[g_running_task_idx].stackPointer);
    if(idx==2){
        ((struct TskContext*)g_tskCbArray[g_running_task_idx].stackPointer)->x30 = TestTaskEntry2;
    }
    LOGI("g_tskCbArray[g_running_task_idx].stackPointer->x30 is 0x%x\n",((struct TskContext*)g_tskCbArray[g_running_task_idx].stackPointer)->x30);
    OsTskContextLoad(g_tskCbArray[g_running_task_idx].stackPointer,((struct TskContext*)g_tskCbArray[g_running_task_idx].stackPointer)->x30);
}
```

### 任务结束处理
任务结束之后，调用 TskExit ，回收分配给该任务的栈区域内存（不回收TCB，因为TCB可重用），并将其标记为可用空闲TCB。
```c
void TskExit(int Tskid){
	PRT_MemFree(0,g_tskCbArray[Tskid].saveAllocStack);
	g_tskCbArray[Tskid].stackSize=0;
}
```
然后，再调用 load_current_context(&g_current_context) ，恢复到 OsMainSchedule 上下文中，找到下一个任务执行。

### 调度改进
现在系统只实现了FIFO调度，如果需要并发，可以引入时钟中断切换，可选的，可以加入任务优先级调度。

若要在ZYC_RtOs 中实现任务中断和切换，需要另外开辟空间保存各个任务的上下文（或者保存在各个任务的栈里），在调度前后保存和恢复上下文（现在ZYC_RtOs只保存了内核的上下文作为一个全局变量）。


### 测试结果
测试代码：
```c
void TestTaskEntry()
{
	LOGI("This is task1 test's entry!!!\n");
	LOGI("How is that run ???\n");
	TskExit(g_running_task_idx);
    load_current_context(&g_current_context);
}
void TestTaskEntry2()
{
	LOGI("This is task2 test's entry!!!\n");
	LOGI("How is that run ???\n");
	TskExit(g_running_task_idx);
	load_current_context(&g_current_context);
}

U32 OsTestInit(void)
{
	    U32 ret;
	        U8 ptNo = OS_MEM_DEFAULT_FSC_PT;
		    struct TskInitParam param = {0};

		    param.stackAddr = PRT_MemAllocAlign(0, ptNo, 0x200, MEM_ADDR_ALIGN_016);
			param.taskEntry = (TskEntryFunc)TestTaskEntry;
			param.taskPrio = 25;
		    param.name = "TestTask";
			param.stackSize = 0x200;

			ret = PRT_TaskCreate(&g_testTskHandle, &param);
			if (ret) {
			    return ret;
			}
			return OS_OK;
}
U32 OsTestInit2(void)
{
	    U32 ret;
	    U8 ptNo = OS_MEM_DEFAULT_FSC_PT;
		struct TskInitParam param = {0};

		param.stackAddr = PRT_MemAllocAlign(0, ptNo, 0x200, MEM_ADDR_ALIGN_016);
		param.taskEntry = (TskEntryFunc)TestTaskEntry2;
		param.taskPrio = 20;
		param.name = "TestTask2";
		param.stackSize = 0x200;
		ret = PRT_TaskCreate(&g_testTskHandle2, &param);
		if (ret) {
		    return ret;
		}
		return OS_OK;
}

void tasks_check(void)
{
	((struct TskContext*)g_tskCbArray[1].stackPointer)->x30 = TestTaskEntry;
	((struct TskContext*)g_tskCbArray[2].stackPointer)->x30 = TestTaskEntry2;
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
    OsTestInit2(); 
    LOGI("g_testTskHandle is %d\n",g_testTskHandle);
	dump_my_task_status();
	tasks_check();
	LOGI("Now We want to sche\n");
	
	OsMainSchedule();
}
```
```
Started cell "inmate-demo-1"
[ZYC_RtOs : INFO] : System alloc mem : begin 2590 , end 12590
[ZYC_RtOs : INFO] : task init begin
[ZYC_RtOs : INFO] : fsc : g_fscMemBitMap is 0x10001
[ZYC_RtOs : INFO] : fsc : g_memTotalSize is 0xffe0
[ZYC_RtOs : INFO] : fsc : g_memUsage is 0x0
[ZYC_RtOs : INFO] : fsc : g_memPeakUsage is 0x0
[ZYC_RtOs : INFO] : fsc : g_memStartAddr is 0x2590
[ZYC_RtOs : INFO] : OS_MAX_TCB_NUM = 5
[ZYC_RtOs : INFO] : sizeof TagTskCb is 88
[ZYC_RtOs : INFO] : g_tskCbArray 's address is 122c0
[ZYC_RtOs : INFO] : task init end
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[1]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[1].node 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackPointer 	is 12168
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackSize 		is 200
[ZYC_RtOs : INFO] : g_tskCbArray[1].taskPid 			is 2
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackCfgFlg 			is 1
[ZYC_RtOs : INFO] : g_tskCbArray[1].priority 			is 25
[ZYC_RtOs : INFO] : g_tskCbArray[1].topOfStack 			is 0x12090
[ZYC_RtOs : INFO] : g_tskCbArray[1].name 			is TestTask
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[2]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[2].node 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackPointer 	is 11f38
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackSize 		is 200
[ZYC_RtOs : INFO] : g_tskCbArray[2].taskPid 			is 3
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackCfgFlg 			is 1
[ZYC_RtOs : INFO] : g_tskCbArray[2].priority 			is 20
[ZYC_RtOs : INFO] : g_tskCbArray[2].topOfStack 			is 0x11e60
[ZYC_RtOs : INFO] : g_tskCbArray[2].name 			is TestTask2
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[3]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[3].node 			is 170a8
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].taskPid 			is 4
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[3].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : Now We want to sche
[ZYC_RtOs : INFO] : find index is 1
[ZYC_RtOs : INFO] : g_running_task_idx is 1
[ZYC_RtOs : INFO] : let's go to task
[ZYC_RtOs : INFO] : g_tskCbArray[g_running_task_idx].stackPointer is 0x12168
[ZYC_RtOs : INFO] : g_tskCbArray[g_running_task_idx].stackPointer->x30 is 0x14008
[ZYC_RtOs : INFO] : This is task1 test's entry!!!
[ZYC_RtOs : INFO] : How is that run ???
[ZYC_RtOs : INFO] : find index is 2
[ZYC_RtOs : INFO] : g_running_task_idx is 2
[ZYC_RtOs : INFO] : let's go to task
[ZYC_RtOs : INFO] : g_tskCbArray[g_running_task_idx].stackPointer is 0x11f38
[ZYC_RtOs : INFO] : g_tskCbArray[g_running_task_idx].stackPointer->x30 is 0x14040
[ZYC_RtOs : INFO] : This is task2 test's entry!!!
[ZYC_RtOs : INFO] : How is that run ???
[ZYC_RtOs : INFO] : no more tasks in system , halt
```
可见，在创建了两个任务之后，进入调度函数，ZYC_RtOs 会依次执行所有创建的任务。任务执行完后，系统停机等待。
