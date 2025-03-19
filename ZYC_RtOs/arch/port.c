//
// Created by zyc on 25-3-18.
//
#include "ZYC_types.h"
#include "task.h"

#define ARMV8_X1_INIT_VALUE     0x01010101UL
#define ARMV8_X2_INIT_VALUE     0x02020202UL
#define ARMV8_X3_INIT_VALUE     0x03030303UL
#define ARMV8_X4_INIT_VALUE     0x04040404UL
#define ARMV8_X5_INIT_VALUE     0x05050505UL
#define ARMV8_X6_INIT_VALUE     0x06060606UL
#define ARMV8_X7_INIT_VALUE     0x07070707UL
#define ARMV8_X8_INIT_VALUE     0x08080808UL
#define ARMV8_X9_INIT_VALUE     0x09090909UL
#define ARMV8_X10_INIT_VALUE    0x10101010UL
#define ARMV8_X11_INIT_VALUE    0x11111111UL
#define ARMV8_X12_INIT_VALUE    0x12121212UL
#define ARMV8_X13_INIT_VALUE    0x13131313UL
#define ARMV8_X14_INIT_VALUE    0x14141414UL
#define ARMV8_X15_INIT_VALUE    0x15151515UL
#define ARMV8_X16_INIT_VALUE    0x16161616UL
#define ARMV8_X17_INIT_VALUE    0x17171717UL
#define ARMV8_X18_INIT_VALUE    0x18181818UL
#define ARMV8_X19_INIT_VALUE    0x19191919UL
#define ARMV8_X20_INIT_VALUE    0x20202020UL
#define ARMV8_X21_INIT_VALUE    0x21212121UL
#define ARMV8_X22_INIT_VALUE    0x22222222UL
#define ARMV8_X23_INIT_VALUE    0x23232323UL
#define ARMV8_X24_INIT_VALUE    0x24242424UL
#define ARMV8_X25_INIT_VALUE    0x25252525UL
#define ARMV8_X26_INIT_VALUE    0x26262626UL
#define ARMV8_X27_INIT_VALUE    0x27272727UL
#define ARMV8_X28_INIT_VALUE    0x28282828UL
#define ARMV8_X29_INIT_VALUE    0x29292929UL

#define ARMV8_SPSR_INIT_VALUE   0x305U   // EL1_SP1 | D | A | I | F

/*
 * 描述: 初始化任务栈的上下文
 */
void *OsTskContextInit(U32 taskID, U32 stackSize, uintptr_t *topStack, uintptr_t funcTskEntry)
{
    (void)taskID;
    struct TskContext *stack = (struct TskContext *)((uintptr_t)topStack + stackSize);

    stack -= 1;

    stack->x00 = 0;
    stack->x01 = ARMV8_X1_INIT_VALUE;
    stack->x02 = ARMV8_X2_INIT_VALUE;
    stack->x03 = ARMV8_X3_INIT_VALUE;
    stack->x04 = ARMV8_X4_INIT_VALUE;
    stack->x05 = ARMV8_X5_INIT_VALUE;
    stack->x06 = ARMV8_X6_INIT_VALUE;
    stack->x07 = ARMV8_X7_INIT_VALUE;
    stack->x08 = ARMV8_X8_INIT_VALUE;
    stack->x09 = ARMV8_X9_INIT_VALUE;
    stack->x10 = ARMV8_X10_INIT_VALUE;
    stack->x11 = ARMV8_X11_INIT_VALUE;
    stack->x12 = ARMV8_X12_INIT_VALUE;
    stack->x13 = ARMV8_X13_INIT_VALUE;
    stack->x14 = ARMV8_X14_INIT_VALUE;
    stack->x15 = ARMV8_X15_INIT_VALUE;
    stack->x16 = ARMV8_X16_INIT_VALUE;
    stack->x17 = ARMV8_X17_INIT_VALUE;
    stack->x18 = ARMV8_X18_INIT_VALUE;
    stack->x19 = ARMV8_X19_INIT_VALUE;
    stack->x20 = ARMV8_X20_INIT_VALUE;
    stack->x21 = ARMV8_X21_INIT_VALUE;
    stack->x22 = ARMV8_X22_INIT_VALUE;
    stack->x23 = ARMV8_X23_INIT_VALUE;
    stack->x24 = ARMV8_X24_INIT_VALUE;
    stack->x25 = ARMV8_X25_INIT_VALUE;
    stack->x26 = ARMV8_X26_INIT_VALUE;
    stack->x27 = ARMV8_X27_INIT_VALUE;
    stack->x28 = ARMV8_X28_INIT_VALUE;
    stack->x29 = ARMV8_X29_INIT_VALUE;
    stack->x30 = funcTskEntry;   // x30： lr(link register)
    stack->xzr = 0;

    stack->elr = funcTskEntry;
    stack->esr = 0;
    stack->far = 0;
    // ARMV8_SPSR_INIT_VALUE   0x305U
    stack->spsr = ARMV8_SPSR_INIT_VALUE;    // EL1_SP1 | D | A | I | F
    return stack;
}
