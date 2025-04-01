/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) ARM Limited, 2014
 *
 * Authors:
 *  Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */


#include <inmate.h>
#include <gic.h>
#include "log.h"
#include "mem.h"
#include "task.h"
#include "ZYC_task.h"
#include "ZYC_mem.h"
#include "fsc_mem.h"
#include "task_external.h"

TskHandle g_testTskHandle;
TskHandle g_testTskHandle2;

//extern struct TagTskCb;
extern struct TskContext g_current_context;
extern int g_running_task_idx;
extern struct TagTskCb *g_tskCbArray;


void TestTaskEntry()
{
	LOGI("This is task1 test's entry!!!\n");
	LOGI("How is that run ???\n");
	TskExit(g_running_task_idx);
load_current_context(&g_current_context);
}
void TestTaskEntry2()
{
	int i = 0;
	LOGI("This is task2 test's entry!!!\n");
	LOGI("How is that run ???\n");
	while(1){
		printk("we halt in task2\n");
		halt();
	}
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


#define BEATS_PER_SEC           10
static u64 ticks_per_beat;
static volatile u64 expected_ticks;

static void handle_IRQ(unsigned int irqn)
{
	        static u64 min_delta = ~0ULL, max_delta = 0;
		        u64 delta;

			        if (irqn != TIMER_IRQ)
					                return;

				        delta = timer_get_ticks() - expected_ticks;
					        if (delta < min_delta)
							                min_delta = delta;
						        if (delta > max_delta)
								                max_delta = delta;

							        printk("Timer fired, jitter: %6ld ns, min: %6ld ns, max: %6ld ns\n",
										               (long)timer_ticks_to_ns(delta),
											                      (long)timer_ticks_to_ns(min_delta),
													                     (long)timer_ticks_to_ns(max_delta));

								        
								        expected_ticks = timer_get_ticks() + ticks_per_beat;
									        timer_start(ticks_per_beat);
}





void inmate_main(void)
{
	printk("Initializing the GIC...\n");
	        irq_init(handle_IRQ);
		        irq_enable(TIMER_IRQ);
			        printk("Initializing the timer...\n");

	ticks_per_beat = timer_get_frequency() / BEATS_PER_SEC;
	        expected_ticks = timer_get_ticks() + ticks_per_beat;
		        timer_start(ticks_per_beat);
    
	int temp = 0;
	while(1){
	//	temp ++;
		while(temp<1000000){temp++;}
		temp = 0;
		printk("rellatsdsdsd???\n");
	}
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
	//dump_per_tskCbArray();
	dump_my_task_status();

	tasks_check();
	LOGI("Now We want to sche\n");



	OsMainSchedule();
}




