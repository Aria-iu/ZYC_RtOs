//
// Created by zyc on 25-2-26.
//
#include "serial.h"

// 向 addr 地址处写入 val
static void mmio_write32(void *addr, uint32_t val)
{
    *((volatile uint32_t*)addr) = val;
}

void uart4_init(){
  // 时钟频率
    uint32_t sclk = 24000000;

}