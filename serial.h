//
// Created by zyc on 25-2-26.
//

#ifndef SERIAL_H
#define SERIAL_H

// NOW we can not enable uart irq
// #define UART7_IRQ

#include "uart.h"

#define IRQ_UART4
#define UART4 0xfe680000                    // serial4 base address
// dw8250 UART registers' offsets
#define UART4_RBR_THR_DLL UART4+0x00
#define UART4_IER_DLH UART4+0x04
#define UART4_IIR_FCR UART4+0x08
#define UART4_LCR UART4+0x0c
#define UART4_MCR UART4+0x10
#define UART4_LSR UART4+0x14
#define UART4_MSR UART4+0x18
#define UART4_SCR UART4+0x1c
#define UART4_LPDLL UART4+0x20
#define UART4_LPDLH UART4+0x24
#define UART4_FAR UART4+0x70
#define UART4_TFR UART4+0x74
#define UART4_RFW UART4+0x78
#define UART4_USR UART4+0x7c
#define UART4_TFL UART4+0x80
#define UART4_RFL UART4+0x84
#define UART4_SSR UART4+0x88
#define UART4_SRTS UART4+0x8c
#define UART4_SBCR UART4+0x90
#define UART4_SDMAM UART4+0x94
#define UART4_SFE UART4+0x98
#define UART4_SRT UART4+0x9c
#define UART4_STET UART4+0xa0
#define UART4_HTX UART4+0xa4
#define UART4_DMASA UART4+0xa8
#define UART4_CPR UART4+0xf4
#define UART4_UCV UART4+0xf8
#define UART4_CTR UART4+0xfc

#define TYPE_CAST(type, val) ((type)(val))
#define UART4_IER_DLH_ADDR(base)  TYPE_CAST(void *, (TYPE_CAST(char *, (base)) + UART4_IER_DLH))

struct dw_uart{
  void* base;
};
const struct dw_uart uart4 = {.base = (void*)UART4};

typedef void * sio_fd_t;

void uart4_init();

sio_fd_t serial_open(void);
// void serial_irq_rx_enable(sio_fd_t fd);
void serial_putchar(sio_fd_t fd, uint32_t c);
void serial_printf(sio_fd_t fd, const char *ctrl1, ...);
// int serial_irq_getchar(sio_fd_t fd);

#endif //SERIAL_H
