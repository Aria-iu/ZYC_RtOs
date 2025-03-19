//
// Created by zyc on 25-3-17.
//
#include "ZYC_types.h"
#include "task.h"

/*
 * 描述: 关闭全局可屏蔽中断。
 */
uintptr_t PRT_HwiLock(void)
{
    uintptr_t state = 0;
    OS_EMBED_ASM(
        "mrs %0, DAIF      \n"
        "msr DAIFSet, %1   \n"
        : "=r"(state)
        : "i"(DAIF_IRQ_BIT)
        : "memory", "cc");
    return state & INT_MASK;
}

/*
 * 描述: 开启全局可屏蔽中断。
 */
uintptr_t PRT_HwiUnLock(void)
{
    uintptr_t state = 0;

    OS_EMBED_ASM(
        "mrs %0, DAIF      \n"
        "msr DAIFClr, %1   \n"
        : "=r"(state)
        : "i"(DAIF_IRQ_BIT)
        : "memory", "cc");

    return state & INT_MASK;
}

/*
 * 描述: 恢复原中断状态寄存器。
 */
void PRT_HwiRestore(uintptr_t intSave)
{
    if ((intSave & INT_MASK) == 0) {
        OS_EMBED_ASM(
            "msr DAIFClr, %0\n"
            :
            : "i"(DAIF_IRQ_BIT)
            : "memory", "cc");
    } else {
        OS_EMBED_ASM(
            "msr DAIFSet, %0\n"
            :
            : "i"(DAIF_IRQ_BIT)
            : "memory", "cc");
    }
    return;
}

void what(void){


}