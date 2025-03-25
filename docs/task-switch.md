## 任务调度
创建任务之后，TCB 存储在 g_tskCbArray 数组中，用户可以自行定义任务的调度，这里实现了 FIFO 的调度，根据任务创建的先后顺序依次执行。

FIFO 的调度方法最为简单，也是单核嵌入式系统的常见选择，但是有很多缺陷，例如，某个任务中若有等待或其他耗时操作，其他任务无法执行。

### 调度改进
现在系统只实现了FIFO调度，如果需要并发，可以引入时钟中断切换，可选的，可以加入任务优先级调度。

若要在ZYC_RtOs 中实现任务中断和切换，需要另外开辟空间保存各个任务的上下文（或者保存在各个任务的栈里），在调度前后保存和恢复上下文（现在ZYC_RtOs只保存了内核的上下文作为一个全局变量）。


### 测试结果
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
[ZYC_RtOs : INFO] : fsc : g_fscMemBitMap is 0x10001
[ZYC_RtOs : INFO] : fsc : g_memTotalSize is 0xffe0
[ZYC_RtOs : INFO] : fsc : g_memUsage is 0x2d8
[ZYC_RtOs : INFO] : fsc : g_memPeakUsage is 0x2d8
[ZYC_RtOs : INFO] : fsc : g_memStartAddr is 0x2590
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[1]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[1].node 			is 170a8
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].taskPid 			is 2
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[1].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[2]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[2].node 			is 12348
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].taskPid 			is 3
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[2].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[3]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[3].node 			is 123d0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].taskPid 			is 4
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[3].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbFreeList's next is 12348
[ZYC_RtOs : INFO] : g_tskCbFreeList's next next is 123d0
[ZYC_RtOs : INFO] : g_tskCbFreeList's next next next is 12458
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev is 12458
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev prev is 123d0
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev prev prev is 12348
[ZYC_RtOs : INFO] : g_testTskHandle is 2
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
可见，在创建了两个任务之后，进入调度函数，ZYC_RtOs 会依次执行所有创建的任务。