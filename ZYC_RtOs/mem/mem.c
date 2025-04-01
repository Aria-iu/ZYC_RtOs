//
// Created by zyc on 25-3-10.
//
#include "mem.h"
#include "mem_config.h"
#include "ZYC_types.h"
#include "fsc_mem.h"
#include "log.h"

// 这里是动态分配/释放使用的内存区域
U8 g_memRegion00[OS_MEM_FSC_PT_SIZE];

void mem_test(int * addr)
{
//    *addr = 0xdeadbeef;
//    int read = *addr;
//    return (read == 0xdeadbeef);
}

void mem_detect(void){
    LOGI("System alloc mem : begin %x , end %x\n",g_memRegion00,g_memRegion00+OS_MEM_FSC_PT_SIZE);
}

void mem_init(void){
    OsFscMemInit(OS_MEM_FSC_PT_ADDR, OS_MEM_FSC_PT_SIZE);
}

void *PRT_MemAlloc(U32 mid, U8 ptNo, U32 size)
{
    void *addr;
    uintptr_t intSave;

    // intSave = PRT_HwiLock();
    addr = g_memArithAPI.alloc(mid, ptNo, size);
    // PRT_HwiRestore(intSave);

    return addr;
}

void *PRT_MemAllocAlign(U32 mid, U8 ptNo, U32 size, enum MemAlign alignPow)
{
    void *addr;
    uintptr_t intSave;

    // intSave = PRT_HwiLock();
    addr = g_memArithAPI.allocAlign(mid, ptNo, size, alignPow);
    // PRT_HwiRestore(intSave);

    return addr;
}

U32 PRT_MemFree(U32 mid, void *addr)
{
    U32 ret;
    uintptr_t intSave;

    (void)mid;
    // intSave = PRT_HwiLock();
    ret = g_memArithAPI.free(addr);
    // PRT_HwiRestore(intSave);

    return ret;
}

