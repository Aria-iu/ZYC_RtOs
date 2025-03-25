//
// Created by zyc on 25-3-17.
//
#include "ZYC_task.h"
#include "ZYC_mem.h"
#include "task.h"
#include "task_external.h"
#include "mem.h"
#include "fsc_mem.h"

extern U32 g_tskMaxNum;
extern struct TagTskCb *g_tskCbArray;
extern void dump_task(int index);

struct TskContext g_current_context;

void save_current_context(struct TskContext* context) {
    asm volatile("mrs %0, elr_el1" : "=r"(context->elr));
    asm volatile("mrs %0, spsr_el1" : "=r"(context->spsr));
    asm volatile("mrs %0, far_el1" : "=r"(context->far));
    asm volatile("mrs %0, esr_el1" : "=r"(context->esr));
    context->xzr = 0;
    asm volatile("mov %0, sp" : "=r"(context->sp));
    asm volatile("mov %0, x0" : "=r"(context->x00));
    asm volatile("mov %0, x1" : "=r"(context->x01));
    asm volatile("mov %0, x2" : "=r"(context->x02));
    asm volatile("mov %0, x3" : "=r"(context->x03));
    asm volatile("mov %0, x4" : "=r"(context->x04));
    asm volatile("mov %0, x5" : "=r"(context->x05));
    asm volatile("mov %0, x6" : "=r"(context->x06));
    asm volatile("mov %0, x7" : "=r"(context->x07));
    asm volatile("mov %0, x8" : "=r"(context->x08));
    asm volatile("mov %0, x9" : "=r"(context->x09));
    asm volatile("mov %0, x10" : "=r"(context->x10));
    asm volatile("mov %0, x11" : "=r"(context->x11));
    asm volatile("mov %0, x12" : "=r"(context->x12));
    asm volatile("mov %0, x13" : "=r"(context->x13));
    asm volatile("mov %0, x14" : "=r"(context->x14));
    asm volatile("mov %0, x15" : "=r"(context->x15));
    asm volatile("mov %0, x16" : "=r"(context->x16));
    asm volatile("mov %0, x17" : "=r"(context->x17));
    asm volatile("mov %0, x18" : "=r"(context->x18));
    asm volatile("mov %0, x19" : "=r"(context->x19));
    asm volatile("mov %0, x20" : "=r"(context->x20));
    asm volatile("mov %0, x21" : "=r"(context->x21));
    asm volatile("mov %0, x22" : "=r"(context->x22));
    asm volatile("mov %0, x23" : "=r"(context->x23));
    asm volatile("mov %0, x24" : "=r"(context->x24));
    asm volatile("mov %0, x25" : "=r"(context->x25));
    asm volatile("mov %0, x26" : "=r"(context->x26));
    asm volatile("mov %0, x27" : "=r"(context->x27));
    asm volatile("mov %0, x28" : "=r"(context->x28));
    asm volatile("mov %0, x29" : "=r"(context->x29));
    asm volatile("mov %0, x30" : "=r"(context->x30));
}

// 辅助函数：打印 TskContext 的内容
void print_context(const TskContext* context) {
    LOGI("TskContext Content:\n");
    LOGI("  elr  : 0x%lx\n", context->elr);
    LOGI("  spsr : 0x%lx\n", context->spsr);
    LOGI("  far  : 0x%lx\n", context->far);
    LOGI("  esr  : 0x%lx\n", context->esr);
    LOGI("  xzr  : 0x%lx\n", context->xzr);
    LOGI("  sp   : 0x%lx\n", context->sp);  // 打印栈指针
    LOGI("  x30  : 0x%lx\n", context->x30);
    LOGI("  x29  : 0x%lx\n", context->x29);
    LOGI("  x28  : 0x%lx\n", context->x28);
    LOGI("  x27  : 0x%lx\n", context->x27);
    LOGI("  x26  : 0x%lx\n", context->x26);
    LOGI("  x25  : 0x%lx\n", context->x25);
    LOGI("  x24  : 0x%lx\n", context->x24);
    LOGI("  x23  : 0x%lx\n", context->x23);
    LOGI("  x22  : 0x%lx\n", context->x22);
    LOGI("  x21  : 0x%lx\n", context->x21);
    LOGI("  x20  : 0x%lx\n", context->x20);
    LOGI("  x19  : 0x%lx\n", context->x19);
    LOGI("  x18  : 0x%lx\n", context->x18);
    LOGI("  x17  : 0x%lx\n", context->x17);
    LOGI("  x16  : 0x%lx\n", context->x16);
    LOGI("  x15  : 0x%lx\n", context->x15);
    LOGI("  x14  : 0x%lx\n", context->x14);
    LOGI("  x13  : 0x%lx\n", context->x13);
    LOGI("  x12  : 0x%lx\n", context->x12);
    LOGI("  x11  : 0x%lx\n", context->x11);
    LOGI("  x10  : 0x%lx\n", context->x10);
    LOGI("  x09  : 0x%lx\n", context->x09);
    LOGI("  x08  : 0x%lx\n", context->x08);
    LOGI("  x07  : 0x%lx\n", context->x07);
    LOGI("  x06  : 0x%lx\n", context->x06);
    LOGI("  x05  : 0x%lx\n", context->x05);
    LOGI("  x04  : 0x%lx\n", context->x04);
    LOGI("  x03  : 0x%lx\n", context->x03);
    LOGI("  x02  : 0x%lx\n", context->x02);
    LOGI("  x01  : 0x%lx\n", context->x01);
    LOGI("  x00  : 0x%lx\n", context->x00);
}

int find_tcb_aviliable(void){
    int i;
    for(i=1; i<=g_tskMaxNum; i++){
        if(g_tskCbArray[i].stackSize!=0){
            return i;
        }
    }
}

void OsMainSchedule(void)
{
  /*
  while(1){
        int idx = find_tcb_aviliable();
        LOGI("find index is %d\n",idx);
        // dump_task(idx);
        // 找到一个已经创建的TCB
        // OsTskContextLoad((uintptr_t)g_tskCbArray[idx].stackPointer);
        g_tskCbArray[idx].taskEntry(g_tskCbArray[idx].args[OS_TSK_PARA_0], g_tskCbArray[idx].args[OS_TSK_PARA_1], g_tskCbArray[idx].args[OS_TSK_PARA_2],
                          g_tskCbArray[idx].args[OS_TSK_PARA_3]);
        // Todo ： 回收这个任务
        g_tskCbArray[idx].stackSize = 0;
  }*/
    int idx = find_tcb_aviliable();
    LOGI("find index is %d\n",idx);
    print_context(g_tskCbArray[idx].stackPointer);
    LOGI("sys_stack_top is 0x%x\n",stack_top);
    save_current_context(g_current_context);
    print_context(g_current_context);
    print_context(g_tskCbArray[idx].stackPointer);
    OsTskContextLoad(g_tskCbArray[idx].stackPointer,((struct TskContext*)g_tskCbArray[idx].stackPointer)->x30);
	// LOGI("ret???");
}