//
// Created by zyc on 25-3-1.
//

#ifndef UART_REGS_H
#define UART_REGS_H

#include <stdint.h>

#define PERI_APB_FREQ       100000000
#define UART4_BASE                     0xFE680000U /* UART4 base address */
#define UART4               ((struct UART_REG *) UART4_BASE)

/*
 * UART register offsets
 */
#define DW_UART_RBR 0x00
#define DW_UART_THR 0x00
#define DW_UART_DLL 0x00

#define DW_UART_DLH 0x04
#define DW_UART_IER 0x04

#define DW_UART_IIR 0x08
#define DW_UART_FCR 0x08

#define DW_UART_LCR 0x0C

#define DW_UART_MCR 0x10

#define DW_UART_LSR 0x14
#define DW_UART_MSR 0x18

#define DW_UART_USR 0x7C
#define DW_UART_TFL 0x80
#define DW_UART_RFL 0x84

#define DW_UART_HTX 0xA4

/* LSR 线性状态寄存器区域 */
#define DW_UART_LSR_TEMT 0x40
#define DW_UART_LSR_THRE 0x20
#define DW_UART_LSR_BI   0x10
#define DW_UART_LSR_FE   0x08
#define DW_UART_LSR_PE   0x04
#define DW_UART_LSR_R    0x02
#define DW_UART_LSR_DDR  0x01

#define BIT(n)           (1 << (n))

/* LCR bit field */
#define DW_UART_DLAB         BIT(7)
#define DW_UART_BREAK        BIT(6)
#define DW_UART_STICK        BIT(5)
#define DW_UART_EPS          BIT(4)
#define DW_UART_PEN          BIT(3)
#define DW_UART_STOP         BIT(2)
#define DW_UART_8bit         0x3
#define DW_UART_7bit         0x2
#define DW_UART_6bit         0x1
#define DW_UART_5bit         0x0
#define DW_UART_DATALEN_MASK 0x03

/* IER bit field */
#define PTIME  BIT(7)
#define EDSSI  BIT(3)
#define ELSI   BIT(2)
#define ETBEI  BIT(1)
#define ERBFI  BIT(0)

/* LSR bit field */
#define DW_RFE   BIT(7)
#define DW_TEMT  BIT(6)
#define DW_THRE  BIT(5)
#define DW_BI    BIT(4)
#define DW_FE    BIT(3)
#define DW_PE    BIT(2)
#define DW_OE    BIT(1)
#define DW_DR    BIT(0)

#define UART_DW_DR_PE DW_PE
#define UART_DW_DR_FE DW_FE
#define UART_DW_DR_OE DW_OE
#define UART_DW_DR_BE DW_BI

#define DW_RSR_ANY  (DW_OE | DW_PE | DW_FE | DW_BI)
#define DW_DUMMY_RSR_RX

/* MCR bit field */
#define DW_MC_AFCE  BIT(5)
#define DW_MC_LOOP  BIT(4)
#define DW_MC_OUT2  BIT(3)
#define DW_MC_OUT1  BIT(2)
#define DW_MC_RTS   BIT(1)
#define DW_MC_DTR   BIT(0)

/* MSR bit field */
#define DW_DCD     BIT(7)
#define DW_RI      BIT(6)
#define DW_DSR     BIT(5)
#define DW_CTS     BIT(4)
#define DW_MSR_ANY (DW_DCD | DW_DSR | DW_CTS)

/* IIR bit field */
#define DW_RECEIVERR       0x06
#define DW_RECEIVEAVA      0x04
#define DW_RECTIMEOUT      0x0C
#define DW_TRANSEMP        0x02
#define DW_NOINTERRUPT     0x01
#define DW_MODEMSTA        0x0
#define DW_BUSY            0x7

/* FCR bit field */
#define RECFIFO1_2     (0x02 << 6)
#define TXFIFO1_2      (0x03 << 4)
#define FIFOENA        1
#define UART_FCR_RXCLR 0x02
#define UART_FCR_TXCLR 0x04

/* USR bit field */
#define DW_UART_BUSY      0x01
#define DW_XFIFO_NOT_FULL 0x02
#define DW_XFIFO_EMP      0x04
#define DW_RFIFO_NOT_EMP  0x08
#define DW_RFIFO_FULL     0x10

/* UART Register Structure Define */
struct UART_REG {
    union {
        __I  uint32_t RBR;                                /* Address Offset: 0x0000 */
        __IO uint32_t DLL;                                /* Address Offset: 0x0000 */
        __O  uint32_t THR;                                /* Address Offset: 0x0000 */
    };
    union {
        __IO uint32_t DLH;                                /* Address Offset: 0x0004 */
        __IO uint32_t IER;                                /* Address Offset: 0x0004 */
    };
    union {
        __O  uint32_t FCR;                                /* Address Offset: 0x0008 */
        __I  uint32_t IIR;                                /* Address Offset: 0x0008 */
    };
    __IO uint32_t LCR;                                /* Address Offset: 0x000C */
    __IO uint32_t MCR;                                /* Address Offset: 0x0010 */
    __I  uint32_t LSR;                                /* Address Offset: 0x0014 */
    __I  uint32_t MSR;                                /* Address Offset: 0x0018 */
    __IO uint32_t SCR;                                /* Address Offset: 0x001C */
         uint32_t RESERVED0020[4];                    /* Address Offset: 0x0020 */
    union {
        __I  uint32_t SRBR;                               /* Address Offset: 0x0030 */
        __O  uint32_t STHR;                               /* Address Offset: 0x0030 */
    };
         uint32_t RESERVED0034[15];                   /* Address Offset: 0x0034 */
    __IO uint32_t FAR;                                /* Address Offset: 0x0070 */
    __I  uint32_t TFR;                                /* Address Offset: 0x0074 */
    __O  uint32_t RFW;                                /* Address Offset: 0x0078 */
    __I  uint32_t USR;                                /* Address Offset: 0x007C */
    __I  uint32_t TFL;                                /* Address Offset: 0x0080 */
    __I  uint32_t RFL;                                /* Address Offset: 0x0084 */
    __O  uint32_t SRR;                                /* Address Offset: 0x0088 */
    __IO uint32_t SRTS;                               /* Address Offset: 0x008C */
    __IO uint32_t SBCR;                               /* Address Offset: 0x0090 */
    __IO uint32_t SDMAM;                              /* Address Offset: 0x0094 */
    __IO uint32_t SFE;                                /* Address Offset: 0x0098 */
    __IO uint32_t SRT;                                /* Address Offset: 0x009C */
    __IO uint32_t STET;                               /* Address Offset: 0x00A0 */
    __IO uint32_t HTX;                                /* Address Offset: 0x00A4 */
    __O  uint32_t DMASA;                              /* Address Offset: 0x00A8 */
         uint32_t RESERVED00AC[18];                   /* Address Offset: 0x00AC */
    __I  uint32_t CPR;                                /* Address Offset: 0x00F4 */
    __I  uint32_t UCV;                                /* Address Offset: 0x00F8 */
    __I  uint32_t CTR;                                /* Address Offset: 0x00FC */
};



#endif //UART_REGS_H
