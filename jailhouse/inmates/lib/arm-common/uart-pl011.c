#include <inmate.h>
#include <uart.h>

#define UARTDR		0x00
#define UARTFR		0x18
#define UARTIBRD	0x24
#define UARTLCR_H	0x2c
#define UARTCR		0x30

#define UARTFR_TXFF	(1 << 5)
#define UARTFR_BUSY	(1 << 3)

#define UARTCR_Out2  	(1 << 13)
#define UARTCR_Out1  	(1 << 12)
#define UARTCR_RXE   	(1 << 9)
#define UARTCR_TXE   	(1 << 8)
#define UARTCR_EN	(1 << 0)

#define UARTLCR_H_WLEN	(3 << 5)

static void uart_pl011_init(struct uart_chip *chip)
{
	if (chip->divider) {
		mmio_write16(chip->base + UARTCR, 0);
		while (mmio_read8(chip->base + UARTFR) & UARTFR_BUSY)
			cpu_relax();
		mmio_write16(chip->base + UARTIBRD, chip->divider);
		mmio_write8(chip->base + UARTLCR_H, UARTLCR_H_WLEN);
		mmio_write16(chip->base + UARTCR, UARTCR_EN | UARTCR_TXE |
						  UARTCR_Out1 | UARTCR_Out2);
	}
}

static bool uart_pl011_is_busy(struct uart_chip *chip)
{
	/* FIFO full or busy */
	return (mmio_read32(chip->base + UARTFR) &
		(UARTFR_TXFF | UARTFR_BUSY)) != 0;
}

static void uart_pl011_write(struct uart_chip *chip, char c)
{
	mmio_write32(chip->base + UARTDR, c);
}

DEFINE_UART(pl011, "PL011", JAILHOUSE_CON_TYPE_PL011);
