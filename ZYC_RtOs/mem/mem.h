//
// Created by zyc on 25-3-10.
//

#ifndef MEM_H
#define MEM_H

#include "ZYC_types.h"
#include "ZYC_module.h"
#include "ZYC_mem.h"

bool mem_test(int * addr);

/* 申请一个内存块 */
typedef void *(*MemAllocFunc)(enum MoudleId mid, U8 ptNo, U32 size);

/* 申请size字节并返回指向已分配内存的指针，内存地址将按照alignPow动态对齐 */
typedef void *(*MemAllocAlignFunc)(U32 mid, U8 ptNo, U32 size, enum MemAlign alignPow);

/* 释放一个内存块  */
typedef U32 (*MemFreeFunc)(void *addr);

struct TagMemFuncLib {
    void *addr;        /* 分区起始地址 */
    MemAllocFunc alloc; /* 申请一个内存块 */
    MemAllocAlignFunc allocAlign; /* 申请size字节并返回指向已分配内存的指针，内存地址将按照alignPow动态对齐 */
    MemFreeFunc free;   /* 释放一个内存块 */
};

#define OS_MEM_HEAD_MAGICWORD       0xABAB /* 内存块的块控制头魔术字，确保为奇数 */

#define OS_MAX_PT_NUM               253

#define OS_MEM_ALIGN_CHECK(value) ((value) & 0x3UL)

#define OS_FSC_MEM_MAGIC_USED                               (struct TagFscMemCtrl *)0x5a5aa5a5
#define OS_FSC_MEM_LAST_IDX                                 31
#define OS_FSC_MEM_USED_HEAD_SIZE                           (sizeof(struct TagFscMemCtrl))
#define OS_FSC_MEM_TAIL_SIZE                                (sizeof(uintptr_t))

#define OS_FSC_MEM_SZGET(currBlk)                           ((U32)(currBlk->size))
#define OS_FSC_MEM_MAXVAL                                   ((1U << OS_FSC_MEM_LAST_IDX) - OS_FSC_MEM_SIZE_ALIGN)

#define OS_FSC_MEM_TAIL_MAGIC                               0xABCDDCBA

/* FSC算法块控制头结构，注意各成员顺序是和其他算法保持一致偏移的，不能随便改动，保持ptNo和其他算法偏移一致 */
struct TagFscMemCtrl {
    struct TagFscMemCtrl *next;
    // 块大小
    uintptr_t size;
    // 若前面相邻的物理块空闲，则此字段记录前面空闲块大小，否则为OS_FSC_MEM_PREV_USED
    uintptr_t prevSize;
    // 空闲时为上一个控制块地址
    struct TagFscMemCtrl *prev;
};

extern void *OsMemAlloc(enum MoudleId mid, U8 ptNo, U32 size);
extern void *OsMemAllocAlign(U32 mid, U8 ptNo, U32 size, enum MemAlign alignPow);

/* 对齐之后，返回地址不一定紧跟在内存头后面，需要设置返回地址与内存头之间的差值 */
OS_SEC_ALW_INLINE INLINE void OsMemSetHeadAddr(uintptr_t usrAddr, uintptr_t ctrlAddr)
{
    U16 *headAddr = (U16 *)(usrAddr) - 1;

    *headAddr  = (U16)(usrAddr - ctrlAddr);
    return;
}

OS_SEC_ALW_INLINE INLINE void *OsMemGetHeadAddr(uintptr_t usrAddr)
{
    U16 headOffset = *((U16 *)usrAddr - 1);

    return (void *)(uintptr_t)((usrAddr - (uintptr_t)headOffset) - sizeof(struct TagFscMemCtrl));
}

OS_SEC_ALW_INLINE INLINE uintptr_t OsMemSetHookAddr(uintptr_t addrress)
{
    return (addrress);
}


extern struct TagMemFuncLib g_memArithAPI; /* 算法对应API */

#define OS_FSC_MEM_SLICE_HEAD_SIZE sizeof(struct TagFscMemCtrl)

void mem_init(void);

#endif //MEM_H
