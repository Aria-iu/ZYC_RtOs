//
// Created by zyc on 25-2-26.
//
#include "serial.h"

#define BAUDRATE 115200
#define UART_SRC_CLK 24000000
#define BST_UART_DLF_LEN  6

const struct dw_uart uart4 = {.base = (void*)UART4};

// 向 addr 地址处写入 val
static void mmio_write32(uint32_t *addr, uint32_t val)
{
    *((volatile uint32_t*)addr) = val;
}

// 向 addr 地址处读取 val
static uint32_t mmio_read32(uint32_t *addr)
{
    return *((volatile uint32_t*)addr);
}

uint32_t get_baud_divider(uint32_t baudrate) {
    return (UART_SRC_CLK << (BST_UART_DLF_LEN - 4)) / baudrate;
}

void dw8250_uart4_init(){
    // 时钟频率
    // uint32_t sclk = 24000000;
    // uint32_t uart_dlf_len = 6;
    // 波特率
    // uint32_t baud_rate = 115200;

    uint32_t divider = get_baud_divider(BAUDRATE);
    // 等待 USR_BUSY 位变为 0
    while ((mmio_read32(UART4_USR_ADDR(uart4.base)) & 0x1) != 0);
    // 禁用中断
    mmio_write32(UART4_IER_DLH_ADDR(uart4.base), 0);
    // 启动 FIFO
    mmio_write32(UART4_IIR_FCR_ADDR(uart4.base), 1);
    // 禁用流控
    mmio_write32(UART4_MCR_ADDR(uart4.base), 0);

    // 设置 MCR_RTS
    uint32_t mcr_val = mmio_read32(UART4_MCR_ADDR(uart4.base));
    mmio_write32(UART4_MCR_ADDR(uart4.base), mcr_val | (1 << 1));

    // 启用 DLAB（访问 DLL 和 DLH）
    uint32_t lcr_val = mmio_read32(UART4_LCR_ADDR(uart4.base));
    mmio_write32(UART4_LCR_ADDR(uart4.base), lcr_val | (1 << 7));

    // 设置波特率分频器
    mmio_write32(UART4_RBR_THR_DLL_ADDR(uart4.base), (divider >> BST_UART_DLF_LEN) & 0xFF); // DLL
    mmio_write32(UART4_IER_DLH_ADDR(uart4.base), (divider >> (BST_UART_DLF_LEN + 8)) & 0xFF); // DLH
    mmio_write32(UART4_DLF_ADDR(uart4.base), divider & ((1 << BST_UART_DLF_LEN) - 1)); // DLF

    // 禁用 DLAB
    lcr_val = mmio_read32(UART4_LCR_ADDR(uart4.base));
    mmio_write32(UART4_LCR_ADDR(uart4.base), lcr_val & ~(1 << 7));

    // 设置数据位长度为 8 位，无校验，1 停止位
    mmio_write32(UART4_LCR_ADDR(uart4.base), mmio_read32(UART4_LCR_ADDR(uart4.base)) | 0x3);
}

void putchar(char c){
    while((mmio_read32(UART4_LSR_ADDR(uart4.base)) & 0x20)==0);
    uint32_t ch = (uint32_t)c;
    mmio_write32(UART4_RBR_THR_DLL_ADDR(uart4.base), ch);
}