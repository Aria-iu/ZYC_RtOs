## 中断管理
实现了 gic-v2 的中断使能，初始化的功能。
```c
// gic-v2.c
#include <gic.h>

#define GICC_CTLR               0x0000
#define GICC_PMR                0x0004
#define GICC_IAR                0x000c
#define GICC_EOIR               0x0010
#define GICD_CTLR               0x0000
#define  GICD_CTLR_ENABLE       (1 << 0)

#define GICC_CTLR_GRPEN1        (1 << 0)

#define GICC_PMR_DEFAULT        0xf0

static void *gicc_v2_base;
static void *gicd_v2_base;

static void gic_v2_enable(unsigned int irqn)
{
        mmio_write32(gicd_v2_base + GICD_ISENABLER + ((irqn >> 3) & ~0x3),
                     1 << (irqn & 0x1f));
}

static int gic_v2_init(void)
{
        gicc_v2_base = (void*)(unsigned long)comm_region->gicc_base;
        gicd_v2_base = (void*)(unsigned long)comm_region->gicd_base;

        map_range(gicc_v2_base, PAGE_SIZE, MAP_UNCACHED);
        map_range(gicd_v2_base, PAGE_SIZE, MAP_UNCACHED);

        mmio_write32(gicc_v2_base + GICC_CTLR, GICC_CTLR_GRPEN1);
        mmio_write32(gicc_v2_base + GICC_PMR, GICC_PMR_DEFAULT);
        mmio_write32(gicd_v2_base + GICD_CTLR, GICD_CTLR_ENABLE);

        return 0;
}

static void gic_v2_write_eoi(u32 irqn)
{
        mmio_write32(gicc_v2_base + GICC_EOIR, irqn);
}

static u32 gic_v2_read_ack(void)
{
        return mmio_read32(gicc_v2_base + GICC_IAR) & 0x3ff;
}

const struct gic gic_v2 = {
        .init = gic_v2_init,
        .enable = gic_v2_enable,
        .write_eoi = gic_v2_write_eoi,
        .read_ack = gic_v2_read_ack,
};

// gic.c
#include <inmate.h>
#include <gic.h>

extern const struct gic gic_v2;

static irq_handler_t irq_handler;
static const struct gic *gic = &gic_v2;

/* Replaces the weak reference in header.S */
void vector_irq(void)
{
        u32 irqn;

        while (1) {
                irqn = gic->read_ack();
                if (irqn == 0x3ff)
                        break;

                if (irq_handler)
                        irq_handler(irqn);

                gic->write_eoi(irqn);
        }
}

void irq_init(irq_handler_t handler)
{
        gic->init();

        irq_handler = handler;

        gic_setup_irq_stack();
}

void irq_enable(unsigned int irq)
{
        gic->enable(irq);
}

```
## 中断测试
测试文件中，将每秒设置为 10 个 beat ， 每个 beat 的时钟 tick 数为 ticks_per_beat。也就是说，每过 ticks_per_beat 个时钟 tick ，认为已经过了 0.1 s。
将 expected_ticks 设置为当前 tick 数加上 ticks_per_beat ，并启动计时器，在下一个 beat 时，触发一次时钟中断。
```c
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
                asm volatile("wfi" : : : "memory");
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

    printk("Timer fired, jitter: %6ld ns, min: %6ld ns, max: %6ld ns\n",(long)timer_ticks_to_ns(delta),
                (long)timer_ticks_to_ns(min_delta),(long)timer_ticks_to_ns(max_delta));
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
    //      temp ++;
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

```

```
Adding virtual PCI device 00:00.0 to cell "inmate-demo-1"
Shared memory connection established, peer cells:
 "Raspberry-Pi4"
Created cell "inmate-demo-1"
Page pool usage after cell creation: mem 76/994, remap 5/131072
Cell "inmate-demo-1" can be loaded
Started cell "inmate-demo-1"
Initializing the GIC...
Initializing the timer...
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
Timer fired, jitter:   3407 ns, min:   3407 ns, max:   3407 ns
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
Timer fired, jitter:   2518 ns, min:   2518 ns, max:   3407 ns
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
Timer fired, jitter:   2462 ns, min:   2462 ns, max:   3407 ns
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???Timer fired, jitter:   4314 ns, min:   2462 ns, max:   4314 ns

rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
Timer fired, jitter:   2462 ns, min:   2462 ns, max:   4314 ns
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsd???
rellatsdsdsdTimer fired, jitter:   5407 ns, min:   2462 ns, max:   5407 ns
???

... ...

Closing cell "inmate-demo-1"
Page pool usage after cell destruction: mem 62/994, remap 5/131072
```

## 使用建议
这里只实现了简单的中断管理，在 Jailhouse 这样的虚拟机管理工具上，分配给 inmate 的中断只有CPU内部的中断（因为一个 inmate 独占一个CPU）和一些共享外设（如UART）的中断。

现在只为 inmate 分配了简单的芯片内部时钟中断并设置为使能。当中断到来时，进行中断处理，时钟间隔大约是 0.1 s。

可以在中断处理程序中实现上下文切换，从而实现并发程序模型，和之前提到的一样，需要实现任务的上下文保存和恢复。