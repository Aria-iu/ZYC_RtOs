//
// Created by zyc on 25-3-10.
//

#ifndef FSC_MEM_H
#define FSC_MEM_H

#include "ZYC_types.h"
#include "ZYC_module.h"
#include "ZYC_mem.h"
#include "mem.h"

/*
 * 模块内宏定义
 */
#define OS_FSC_MEM_PREV_USED 0
#define OS_FSC_MEM_USED_MAGIC OS_MEM_HEAD_MAGICWORD

#define OS_FSC_MEM_SZ2IDX(size) (31 - OsGetLmb1((U32)(size)))
#define OS_FSC_MEM_IDX2BIT(idx) (0x80000000UL >> (idx))

#define OS_FSC_MEM_SIZE_ALIGN OS_MEM_ADDR_ALIGN
#define OS_FSC_MEM_MIN_SIZE (OS_FSC_MEM_SLICE_HEAD_SIZE + OS_FSC_MEM_SIZE_ALIGN)


extern struct TagMemFuncLib g_memArithAPI; /* 算法对应API */
extern struct TagFscMemCtrl g_fscMemNodeList[OS_FSC_MEM_LAST_IDX];
extern U32 g_fscMemBitMap;
extern uintptr_t g_memTotalSize;
extern uintptr_t g_memUsage;
extern uintptr_t g_memPeakUsage;
extern uintptr_t g_memStartAddr;

/*
 * 模块内全局变量声明
 */

/*
 * 模块内函数声明
 */
extern void *OsFscMemSplit(U8 ptNo, uintptr_t size, uintptr_t align,
                           struct TagFscMemCtrl *fscFreeListHead, U32 *bitMapPtr);
extern U32 OsMemPtParaCheck(uintptr_t addr, uintptr_t size, uintptr_t *ptAddr);

U32 OsGetLmb1(U32 value);

/*
 * 模块内内联函数定义
 */
OS_SEC_ALW_INLINE INLINE void OsFscMemDelete(struct TagFscMemCtrl *currBlk)
{
    currBlk->next->prev = currBlk->prev;
    currBlk->prev->next = currBlk->next;
}

OS_SEC_ALW_INLINE INLINE void OsFscMemInsert(struct TagFscMemCtrl *currBlk,
                                             struct TagFscMemCtrl *fscFreeList,
                                             U32 *bitMapPtr)
{
    U32 idx = OS_FSC_MEM_SZ2IDX(currBlk->size);
    struct TagFscMemCtrl *headBlk = &(fscFreeList[idx]);

    *bitMapPtr |= OS_FSC_MEM_IDX2BIT(idx);

    currBlk->prev = headBlk;
    currBlk->next = headBlk->next;
    headBlk->next->prev = currBlk;
    headBlk->next = currBlk;
}

OS_SEC_ALW_INLINE INLINE void OsFscMemBlockInit(struct TagFscMemCtrl *memBlk)
{
    /* 后续考虑整块内存初始化为随机值，当前仅清零控制头 */
    memBlk->next = NULL;
    memBlk->size = 0;
    memBlk->prevSize = 0;
    memBlk->prev = NULL;
}

U32 OsFscMemInit(uintptr_t addr, U32 size);
#endif //FSC_MEM_H
