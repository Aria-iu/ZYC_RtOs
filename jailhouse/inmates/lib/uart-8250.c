#include <inmate.h>
#include <uart.h>

#define UART_TX			0x0
#define UART_DLL		0x0
#define UART_DLM		0x1
#define UART_LCR		0x3
#define  UART_LCR_8N1		0x03
#define  UART_LCR_DLAB		0x80
#define UART_LSR		0x5
#define  UART_LSR_THRE		0x20
#define  UART_MDR1		0x8

static void reg_out_mmio32(struct uart_chip *chip, unsigned int reg, u32 value)
{
	        mmio_write32(chip->base + reg * 4, value);
}

static u32 reg_in_mmio32(struct uart_chip *chip, unsigned int reg)
{
	        return mmio_read32(chip->base + reg * 4);
}

static void uart_8250_init(struct uart_chip *chip)
{
	if (chip->divider) {
		chip->reg_out(chip, UART_LCR, UART_LCR_DLAB);
		chip->reg_out(chip, UART_DLL, chip->divider);
		chip->reg_out(chip, UART_DLM, 0);
		chip->reg_out(chip, UART_LCR, UART_LCR_8N1);
		if (CON_HAS_MDR_QUIRK(comm_region->console.flags))
			chip->reg_out(chip, UART_MDR1, 0);
	}
}

static bool uart_8250_is_busy(struct uart_chip *chip)
{
	return !(chip->reg_in(chip, UART_LSR) & UART_LSR_THRE);
}

static void uart_8250_write(struct uart_chip *chip, char c)
{
	chip->reg_out(chip, UART_TX, c);
}

DEFINE_UART_REG(8250, "8250", JAILHOUSE_CON_TYPE_8250,
		reg_out_mmio32, reg_in_mmio32);
