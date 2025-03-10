//
// Created by zyc on 25-3-10.
//
#include "mem.h"
#include "mem_config.h"

bool mem_test(int * addr)
{
    *addr = 0xdeadbeef;
    int read = *addr;
    return (read == 0xdeadbeef);
}